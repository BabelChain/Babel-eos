var EOS = require('eosjs');

var eosClient = EOS(
    {
        keyProvider: ['5KVuf8b8pePBsjTfYn3X3L3DayK6dftQiV9jfxGbNseiYfBcBYR'],
        httpEndpoint: 'http://10.101.2.109:8888' // EOS http endpoint
    }
)

var account_name = "babel.joe";


// 获取用户信息 
eosClient.getTableRows(true, 'babel.user', account_name, "user").then((data) => {

    console.log(data.rows)

}).catch((e) => {
    console.error(e);
})

//根据用户名 获取视频列表
eosClient.getTableRows(true, 'babel.user', account_name, "video").then((data) => {
    console.log(data.rows)
}).catch((e) => {
    console.error(e);
})