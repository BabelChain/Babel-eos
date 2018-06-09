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
    void like(account_name author, account_name user, const uint64_t id)
    {
        video_index videos(_self, author);
        auto v_itr = videos.find(id);
        eosio_assert(v_itr != videos.end(), "videos not found ");

        user_index author_table(_self, author);
        auto a_itr = author_table.find(author);
        eosio_assert(a_itr != author_table.end(), "unknown author");

        user_index users_table(_self, user);
        auto u_itr = users_table.find(user);
        eosio_assert(u_itr != users_table.end(), "unknown user");

        // video balance 、 vote + 1
        videos.modify(v_itr, 0, [&](auto &_video) {
            _video.ups++;
            _video.balance += asset(10000, S(4, DJB));
        });

        // author ++ up
        author_table.modify(a_itr, 0, [&](auto &acnt) {
            acnt.ups++;
        });

        // voter balance +
        users_table.modify(u_itr, 0, [&](auto &acnt) {
            acnt.balance += asset(10000, S(4, DJB));
        });

        log_index logs(_self, user);

        logs.emplace(_self, [&](auto &new_log) {
            new_log.id = logs.available_primary_key();
            new_log.owner = author;
            new_log.type = 1;
            new_log.description = "Vote";
            new_log.quantity = asset(10000, S(4, DJB));
        });

        eosio::print("like#", author, " success");
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

        eosio::print("booking#", bar, user, quantity, inviter);

        if (inviter_itr != users_inviter.end())
        {
            eosio::print("booking has inviter#");

            // 消费 100%
            users.modify(users_itr, 0, [&](auto &acnt) {
                eosio_assert(acnt.balance >= quantity, "insufficient balance");
                acnt.balance -= quantity;
            });

            log_index logs(_self, user);

            logs.emplace(_self, [&](auto &new_log) {
                new_log.id = logs.available_primary_key();
                new_log.owner = user;
                new_log.type = 0;
                new_log.description = "订座";
                new_log.quantity = quantity;
            });

            // 酒吧 80%
            users_bar.modify(bar_itr, 0, [&](auto &acnt) {
                acnt.balance += asset(quantity.amount * 0.8, S(4, DJB));
            });

            log_index bar_logs(_self, bar);

            bar_logs.emplace(_self, [&](auto &new_log) {
                new_log.id = bar_logs.available_primary_key();
                new_log.owner = bar;
                new_log.type = 1;
                new_log.description = "订座";
                new_log.quantity = asset(quantity.amount * 0.8, S(4, DJB));
                ;
            });

            // 佣金 20%
            users_inviter.modify(inviter_itr, 0, [&](auto &acnt) {
                acnt.balance += asset(quantity.amount * 0.2, S(4, DJB));
            });

            log_index inviter_logs(_self, inviter);

            inviter_logs.emplace(_self, [&](auto &new_log) {
                new_log.id = inviter_logs.available_primary_key();
                new_log.owner = inviter;
                new_log.type = 1;
                new_log.description = "推广分佣";
                new_log.quantity = asset(quantity.amount * 0.2, S(4, DJB));
            });
        }
        else
        {

            eosio::print("booking no inviter#", bar, user, quantity, inviter);
            // 消费 100%
            users.modify(users_itr, 0, [&](auto &acnt) {
                eosio_assert(acnt.balance >= quantity, "insufficient balance");
                acnt.balance -= quantity;
            });

            log_index logs(_self, user);

            logs.emplace(_self, [&](auto &new_log) {
                new_log.id = logs.available_primary_key();
                new_log.owner = user;
                new_log.type = 0;
                new_log.description = "订座";
                new_log.quantity = quantity;
            });

            // 酒吧 100%
            users_bar.modify(bar_itr, 0, [&](auto &acnt) {
                acnt.balance += quantity;
            });

            log_index bar_logs(_self, bar);

            bar_logs.emplace(_self, [&](auto &new_log) {
                new_log.id = bar_logs.available_primary_key();
                new_log.owner = bar;
                new_log.type = 1;
                new_log.description = "订座";
                new_log.quantity = quantity;
                ;
            });
        }
    }

    // 1. 用户买票消费100 DJB ， 票（id，状态，酒吧id，owner）

    // 2. 酒吧可以看到卖出的票，并且可以把其中某个票 的状态标记已经使用

    // 3. 用户每天可以点赞10次，点赞获得10 DJB

    // 分享按钮 生成视频分析链接 链接中带入 推广人xx、酒吧xx

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

        asset balance = asset(5000000, S(4, DJB));
        uint64_t flag = 0;    //标记 0 普通群众，1 酒吧， 2-8 DJ，艺人等角色
        uint64_t age = 0;     //年纪
        uint64_t address = 0; //地址
        uint64_t fans = 0;    //粉丝
        uint64_t follow = 0;  //关注
        uint64_t ups = 0;     //赞
        uint64_t coin = 0;    //币值
        uint64_t card = 0;    //卡券
        uint64_t energy = 0;  //卡券

        std::string name;   //昵称
        std::string avatar; //头像

        EOSLIB_SERIALIZE(user, (id)(owner)(balance)(flag)(age)(address)(fans)(follow)(ups)(coin)(card)(energy)(name)(avatar))
    };

    // @abi table log i64
    struct log
    {
        uint64_t id;
        uint64_t type; //增、减
        account_name owner;
        std::string description;
        asset quantity;

        uint64_t primary_key() const { return id; }
        EOSLIB_SERIALIZE(log, (id)(type)(owner)(description)(quantity))
    };

    // @abi table video i64
    struct video
    {
        uint64_t id;
        account_name owner;
        asset balance = asset(0, S(4, DJB));
        std::string description;
        std::string title;
        std::string address;
        uint64_t ups;
        uint64_t comment;
        uint64_t share;

        uint64_t primary_key() const { return id; }
        EOSLIB_SERIALIZE(video, (id)(owner)(balance)(description)(title)(address)(ups)(comment)(share))
    };

    typedef eosio::multi_index<N(user), user> user_index;

    typedef eosio::multi_index<N(video), video> video_index;

    typedef eosio::multi_index<N(log), log> log_index;
};

EOSIO_ABI(babel, (hi)(signup)(post)(like)(add)(sub)(booking))
