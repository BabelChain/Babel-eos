#include <eosiolib/currency.hpp>
#include <math.h>
#include <eosiolib/dispatcher.hpp>

using namespace eosio;
using eosio::asset;
using eosio::symbol_type;
using eosio::permission_level;
using eosio::action;

class babel : public eosio::contract
{
  public:
    babel(account_name self)
        : eosio::contract(self)
    {
    }

    /// @abi action
    void hi(account_name user)
    {
        eosio::print("Hello Babel, ", name{user});
    }

    // @abi action
    void signup(account_name author,
                const uint32_t id,
                const std::string &name,
                const std::string &avatar)
    {
        user_index users(_self, author);

        users.emplace(_self, [&](auto &acnt) {
            acnt.id = id;
            acnt.owner = author;
            acnt.name = name;
            acnt.avatar = avatar;
        });

        eosio::print("account#", id, name, " created");
    }

    // @abi action
    void post(account_name author,
              const uint32_t id,
              const std::string &title,
              const std::string &description,
              const std::string &address)
    {
        video_index videos(_self, author);

        videos.emplace(_self, [&](auto &new_video) {
            new_video.id = id;
            new_video.owner = author;
            new_video.description = description;
            new_video.title = title;
            new_video.address = address;
        });

        eosio::print("add_video#", id, title, " created");
    }

    // @abi action
    void like(account_name author, const uint32_t id, const uint64_t status)
    {
        video_index videos(_self, author);
        auto v_itr = videos.find(id);

        user_index users(_self, author);
        auto u_itr = users.find(author);

        eosio_assert(u_itr != users.end(), "unknown account");

        // video vote + 1

        // voter balance +

        //

        eosio::print("like#", author, status, " created");
    }

    // @abi action
    void booking(account_name bar, account_name user, const asset &quantity, account_name inviter)
    {
        // inviter： 邀请人，如果传入有效邀请人，智能合约会执行推广返佣的代码。所以前端要判断好，是否是邀请人。 ： 那当前定的酒吧和记录的推广人id、酒吧id比较

        user_index users_bar(_self, bar);
        auto bar_itr = users_bar.find(bar);
        eosio_assert(bar_itr != users_bar.end(), "unknown bar");

        user_index users(_self, user);
        auto users_itr = users.find(user);
        eosio_assert(users_itr != users.end(), "unknown user");

        eosio_assert(quantity.amount > 0, "must give positive quantity");

        user_index users_inviter(_self, inviter);
        auto inviter_itr = users_inviter.find(inviter);
        if (inviter_itr != users_inviter.end())
        {
            // 消费 100% 
            users.modify(users_itr, 0, [&](auto &acnt) {
                eosio_assert(acnt.balance >= quantity, "insufficient balance");
                acnt.balance -= quantity ;
            });

             // 酒吧 80%
            users_bar.modify(bar_itr, 0, [&](auto &acnt) {
                acnt.balance += quantity * 0.8;
            });

            // 佣金 20% 
            users_inviter.modify(inviter_itr, 0, [&](auto &acnt) {
                acnt.balance += quantity * 0.2;
            });
        }
        else
        {
             // 消费 100% 
            users.modify(users_itr, 0, [&](auto &acnt) {
                eosio_assert(acnt.balance >= quantity, "insufficient balance");
                acnt.balance -= quantity ;
            });

             // 酒吧 100%
            users_bar.modify(bar_itr, 0, [&](auto &acnt) {
                acnt.balance += quantity ;
            });

        }
    }

    // 1. 用户买票消费100 DJB ， 票（id，状态，酒吧id，owner）

    // 2. 酒吧可以看到卖出的票，并且可以把其中某个票 的状态标记已经使用

    // 3. 用户每天可以点赞10次，点赞获得10 DJB

    // 分享按钮 生成视频分析链接 链接中带入 推广人id、酒吧id

    // 另一个用户 点击视频分享 获取 推广人id、酒吧id。

    // @abi action
    void add(const account_name to, const asset &quantity)
    {

        eosio_assert(quantity.amount > 0, "must add positive quantity");

        user_index users(_self, to);

        auto itr = users.find(to);
        eosio_assert(itr != users.end(), "unknown account");

        users.modify(itr, 0, [&](auto &acnt) {
            acnt.balance += quantity;
        });

        eosio::print("addToken#", to, quantity);
    }

    // @abi action
    void sub(const account_name to, const asset &quantity)
    {

        eosio_assert(quantity.amount > 0, "must sub positive quantity");
        user_index users(_self, to);

        auto itr = users.find(to);
        eosio_assert(itr != users.end(), "unknown account");

        users.modify(itr, 0, [&](auto &acnt) {
            eosio_assert(acnt.balance >= quantity, "insufficient balance");
            acnt.balance -= quantity;
        });

        eosio::print("subToken#", to, quantity);
    }

  private:
    // @abi table user i64
    struct user
    {
        uint64_t id;

        account_name owner;

        uint64_t primary_key() const { return owner; }

        asset balance = asset(100, S(4, DJB));
        uint32_t flag = 0;    //标记 0 普通群众，1 酒吧， 2-8 DJ，艺人等角色
        uint32_t age = 0;     //年纪
        uint32_t address = 0; //地址
        uint32_t fans = 0;    //粉丝
        uint32_t follow = 0;  //关注
        uint32_t ups = 0;     //赞
        uint32_t coin = 0;    //币值
        uint32_t card = 0;    //卡券
        uint32_t energy = 0;  //卡券

        std::string name;   //昵称
        std::string avatar; //头像

        EOSLIB_SERIALIZE(user, (id)(owner)(balance)(flag)(age)(address)(fans)(follow)(ups)(coin)(card)(energy)(name)(avatar))
    };

    // @abi table video i64
    struct video
    {
        uint64_t id;
        account_name owner;
        std::string description;
        std::string title;
        std::string address;
        uint64_t ups;
        uint64_t comment;
        uint64_t share;

        uint64_t primary_key() const { return id; }
        EOSLIB_SERIALIZE(video, (id)(owner)(description)(title)(address)(ups)(comment)(share))
    };

    typedef eosio::multi_index<N(user), user> user_index;

    typedef eosio::multi_index<N(video), video> video_index;
};

EOSIO_ABI(babel, (hi)(signup)(post)(like)(add)(sub)(booking))
