<template>
	<div class="w750">
		<header>
			<div class="header-box">
				<a href="javascript:window.history.back();" class="header-img tal"><img src="../assets/images/back.png" alt=""></a>
				<p class="header-txt"></p>
				<a href="#" class="header-img tar"></a>
			</div>
		</header>
		<div class="user">
			<!-- 背景 -->
			<div class="user-mask"></div>
			<!-- /背景 -->
			<!-- 用户信息 -->
			<div class="user-info">
				<a href="#" class="user-img"><img src="../assets/img/user-bg.jpg" alt=""></a>
				<div class="user-follow clear">
					<a href="#" class="item"><img src="../assets/images/more.png" alt=""></a>
					<a href="#" class="item"><img src="../assets/images/share.png" alt=""></a>
					<a href="#" class="item flo">+关注</a>
				</div>
			</div>
			<div class="user-name">
				<div class="name-msg">
					<p class="name">用户姓名</p>
					<span class="u-id">用户ID：22880036</span>
				</div>
				<a href="#" class="wb-index">
					<em class="log"><img src="../assets/images/weibo.png" alt=""></em>
					<span class="txt">微博主页</span>
					<i class="arr">&gt;</i>
				</a>
			</div>
			<!-- /用户信息 -->
			<!-- 认证信息 -->
			<div class="user-aut">
				<div class="aut-info">
					<p class="aut-log"><img src="../assets/images/aut-log.png" alt="">认证信息</p>
					<p class="wb-name">微博：微博姓名</p>
					<p class="wb-dse">个人说明，该用户没有留下说明</p>
					<div class="person-tag"><span class="tag01">地区</span><span class="tag02">星座</span></div>
				</div>
				<router-link to="/wallet"><a href="#" class="aut-wallet"><img src="../assets/images/account.png" alt=""></a></router-link>
			</div>
			<!-- /认证信息 -->
			<!-- 粉丝 -->
			<div class="user-fan clear">
				<a href="#" class="item"><em class="num">668</em>关注</a>
				<a href="#" class="item"><em class="num">33.4w</em>粉丝</a>
				<a href="#" class="item"><em class="num">5593</em>获赞</a>
			</div>
			<!-- /粉丝 -->
			<!-- 列表 -->
			<div class="user-list">
				<div class="lis-tab clear">
					<a href="#" class="item current">作品<em class="num">1125</em></a>
					<a href="#" class="item">喜欢<em class="num">86559</em></a>
				</div>
				<div class="list-con clear">
					<router-link to="/playVideo">
						<a href="#" class="list-item">
							<span class="lis-vid"><img src="../assets/img/index-img02.jpg" alt=""></span>
							<em class="like-num">993</em>
						</a>
					</router-link>
					<a href="#" class="list-item">
						<span class="lis-vid"><img src="../assets/img/index-img01.jpg" alt=""></span>
						<em class="like-num">993</em>
					</a>
					<a href="#" class="list-item">
						<span class="lis-vid"><img src="../assets/img/user-bg.jpg" alt=""></span>
						<em class="like-num">993</em>
					</a>
					<a href="#" class="list-item">
						<span class="lis-vid"><img src="../assets/img/user-bg.jpg" alt=""></span>
						<em class="like-num">993</em>
					</a>
					<a href="#" class="list-item">
						<span class="lis-vid"><img src="../assets/img/index-img01.jpg" alt=""></span>
						<em class="like-num">993</em>
					</a>
					<a href="#" class="list-item">
						<span class="lis-vid"><img src="../assets/img/index-img02.jpg" alt=""></span>
						<em class="like-num">993</em>
					</a>
				</div>
				<div class="no-more">没有更多了~</div>
			</div>
			<!-- /列表 -->
		</div>
	</div>
</template>

<script>

import EOS from 'eosjs'

const EOS_CONFIG = {
	contractName: "babel.user", // Contract name
	contractSender: "babel.user", // User executing the contract (should be paired with private key)
	clientConfig: {
		keyProvider: ['5KVuf8b8pePBsjTfYn3X3L3DayK6dftQiV9jfxGbNseiYfBcBYR'], // Your private key
		// httpEndpoint: 'http://127.0.0.1:8888', // EOS http endpoint
		httpEndpoint: 'http://203.223.209.25:8888' // EOS http endpoint
	}
}

export default {
  name: 'User',
  data () {
    return {
      msg: 'Welcome to Your User'
    }
  },

  created () {
  	this.eosClient = EOS.Localnet(EOS_CONFIG.clientConfig)
  },

  mounted () {

  	//获取用户信息
  	this.eosClient.getTableRows(true, EOS_CONFIG.contractName, EOS_CONFIG.contractSender, "user").then((data) => {
		var uid = 0;
		data.rows.map(row => {
			console.log(row);
		});
	}).catch((e) => {
		console.error(e);
	})
  },

  methods: {

  }
}

</script>

<style>
@import "../assets/css/user.css";
</style>