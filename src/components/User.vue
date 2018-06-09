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
					<a @click="followUser()" href="#" :class="isFollow?'item disflo':'item flo'">{{isFollow?'取消关注':'关注'}}</a>
				</div>
			</div>
			<div class="user-name">
				<div class="name-msg">
					<p class="name">{{userName}}</p>
					<span class="u-id">用户ID：{{userId}}</span>
				</div>
			</div>
			<!-- /用户信息 -->
			<!-- 认证信息 -->
			<div class="user-aut">
				<div class="aut-info">
					<!-- <p class="aut-log"><img src="../assets/images/aut-log.png" alt="">认证信息</p> -->
					<!-- <p class="wb-name">微博：微博姓名</p> -->
					<p class="wb-dse">个人说明，该用户没有留下说明</p>
					<div class="person-tag"><span class="tag01">地区</span><span class="tag02">星座</span></div>
				</div>
				<router-link to="/wallet">
					<a href="#" class="aut-wallet"><img src="../assets/images/account.png" alt=""></a>
				</router-link>
			</div>
			<!-- /认证信息 -->
			<!-- 粉丝 -->
			<div class="user-fan clear">
				<a href="#" class="item"><em class="num">{{follow}}</em>关注</a>
				<a href="#" class="item"><em class="num">{{fans}}</em>粉丝</a>
				<a href="#" class="item"><em class="num">{{ups}}</em>获赞</a>
			</div>
			<!-- /粉丝 -->
			<!-- 列表 -->
			<div class="user-list">
				<div class="lis-tab clear">
					<a href="#" class="item current">作品<em class="num">1125</em></a>
					<a href="#" class="item">喜欢<em class="num">86559</em></a>
				</div>
				<div class="list-con clear">
					<a href="#" class="list-item" v-for="(item, index) in videoList">
						<span class="lis-vid"><img :src="videoImgs[index]" alt=""></span>
						<em class="like-num">{{item.ups}}</em>
					</a>
				</div>
				<div class="no-more">没有更多了~</div>
			</div>
			<!-- /列表 -->
		</div>
	</div>
</template>

<script>
	import videoImg0 from "../assets/img/video-0.png"
	import videoImg1 from "../assets/img/video-1.png"
	import videoImg2 from "../assets/img/video-2.png"
	import videoImg3 from "../assets/img/video-3.png"
	import videoImg4 from "../assets/img/video-4.png"
	import videoImg5 from "../assets/img/video-5.png"

	import EOS from 'eosjs'
	var eos;
	const EOS_CONFIG = {
		contractName: "babel.user", // Contract name
		contractSender: "babel.joe", // User executing the contract (should be paired with private key)
		clientConfig: {
			keyProvider: ['5KVuf8b8pePBsjTfYn3X3L3DayK6dftQiV9jfxGbNseiYfBcBYR'], 
			httpEndpoint: 'http://10.101.2.109:8888' // EOS http endpoint
		}
	}

	export default {
		name: 'User',
		data() {
			return {
				isScatter: false,
				isFollow: false,
				userId: "",
				userName: "",
				follow: 0,
				fans: 0,
				ups: 0,
				videoList: [],
				videoImgs: [videoImg0, videoImg1, videoImg2, videoImg3, videoImg4, videoImg5]
			}
		},

		created() {
			
/*			const network = {
				blockchain: 'eos',
				host: '10.101.2.109', // ( or null if endorsed chainId )
				port: 8888, // ( or null if defaulting to 80 )
				chainId: 1 || 'cf057bbfb72640471fd910bcb67639c22df9f92470936cddc1ade0e2f2e7dc4f', // Or null to fetch automatically ( takes longer )
			}

			document.addEventListener('scatterLoaded', scatterExtension => {
				// Scatter will now be available from the window scope.
				// At this stage the connection to Scatter from the application is 
				// already encrypted. 
				const scatter = window.scatter;

				// It is good practice to take this off the window once you have 
				// a reference to it.
				window.scatter = null;

				// If you want to require a specific version of Scatter
				scatter.requireVersion(3.0);
				this.isScatter = true;
				console.log("scatter installed")

				// Set up any extra options you want to use eosjs with. 
				const eosOptions = {};

				// Get a reference to an 'Eosjs' instance with a Scatter signature provider.
				eos = scatter.eos(network, EOS, eosOptions, 'http');

			})*/
			this.eosClient = EOS(EOS_CONFIG.clientConfig);
		},

		mounted() {

			this.eosClient.getTableRows(true, EOS_CONFIG.contractName, "babel.joe", "user").then((data) => {

					if (data.rows && data.rows.length) {
						var user = data.rows[0];

						this.userId = user.id;
						this.userName = user.name;
						this.follow = user.follow;
						this.fans = user.fans;
						this.ups = user.ups;

						this.eosClient.getTableRows(true, EOS_CONFIG.contractName, user.owner, "video").then((data) => {
							if (data.rows && data.rows.length) {

								this.videoList = data.rows;
							}
						}).catch((e) => {
							console.error(e);
						});
					}



				}).catch((e) => {
					console.error(e);
				})
		},

		methods: {
			followUser: function(){
				if(this.isFollow){
					this.isFollow = false;
				}else{
					this.isFollow = true;
				}
			}
		}
	}

</script>

<style>
	@import "../assets/css/user.css";
</style>