var EOS = require('eosjs');

var contract_name = "babel.user"

var eosClient = EOS(
    {
        keyProvider: ['5KVuf8b8pePBsjTfYn3X3L3DayK6dftQiV9jfxGbNseiYfBcBYR'], // 直接提供私钥。后续应该用scatter方案来替换。
        httpEndpoint: 'http://10.101.2.109:8888' // EOS http endpoint
    }
)

var account_name = "babel.joe";


// demo1 获取用户信息 
// eosClient.getTableRows(true, contract_name, account_name, "user").then((data) => {

//     console.log(data.rows)

// }).catch((e) => {
//     console.error(e);
// })

//demo2 根据用户名 获取视频列表
// eosClient.getTableRows(true, contract_name, account_name, "video").then((data) => {
//     console.log(data.rows)
// }).catch((e) => {
//     console.error(e);
// })

// cleos push action babel.user booking '["babel.joe","babel.user", "1.0000 DJB","xxx"]' -p babel.joe

//demo3 定座 场景 
var bar_name = "babel.joe"
var user_name = "babel.user"
var money = "1.0000 DJB"
var inviter = "babel.alice"

eosClient.contract(contract_name).then((contract) => {
    contract.booking(bar_name, user_name, money, inviter, { authorization: [user_name] }).then((res) => {
        console.log(res)
    }).catch((err) => {
        console.log(err)
    })
})

//demo4 余额变动记录
// eosClient.getTableRows(true, contract_name, account_name, "log").then((data) => {
//     console.log(data.rows)
// }).catch((e) => {
//     console.error(e);
// })

//demo5 投票 
var author_name = "babel.joe"
var user_name = "babel.user"
var video_id = 1

eosClient.contract(contract_name).then((contract) => {
    contract.like(author_name, user_name, video_id, { authorization: [user_name] }).then((res) => {
        console.log(res)
    }).catch((err) => {
        console.log(err)
    })
})

