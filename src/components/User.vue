<template>
	<div class="w750">
		<header>
			<div class="header-box">
				<router-link :to="{name:'Index'}">
					<a class="header-img tal"><img src="../assets/images/back.png" alt=""></a>
				</router-link>
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
				<a href="#" class="user-img">

					<img v-if="flag != null" :src="portraits[flag]" alt="">
					<!-- <img v-else src="../assets/img/user-bg.jpg" alt=""> -->
				</a>
				<div class="user-follow clear">
					<!-- <a href="#" class="item"><img src="../assets/images/more.png" alt=""></a>
					<a href="#" class="item"><img src="../assets/images/share.png" alt=""></a> -->
					<a @click="followUser()" href="#" :class="isFollow?'item disflo':'item flo'">{{isFollow?'取消关注':'关注'}}</a>
				</div>
			</div>
			<div class="user-name">
				<div class="name-msg">
					<p class="name">{{userName}}</p>
					<span class="u-id">account：{{owner}}</span>
				</div>
			</div>
			<!-- /用户信息 -->
			<!-- 认证信息 -->
			<div class="user-aut">
				<div class="aut-info">
					<!-- <p class="aut-log"><img src="../assets/images/aut-log.png" alt="">认证信息</p> -->
					<!-- <p class="wb-name">微博：微博姓名</p> -->
					<p class="wb-dse">{{desc}}</p>
					<!-- <div class="person-tag"><span class="tag01">地区</span><span class="tag02">星座</span></div> -->
				</div>
				<router-link :to="{name:'Wallet', params: {owner:owner}}">
					<a href="#" class="aut-wallet"><img src="../assets/images/account.png" alt=""></a>
				</router-link>
			</div>
			<!-- /认证信息 -->
			<!-- 粉丝 -->
			<div class="user-fan clear">
				<a href="#" class="item"><em class="num">{{follow}}</em>follow</a>
				<a href="#" class="item"><em class="num">{{fans}}</em>followers</a>
				<a href="#" class="item"><em class="num">{{ups}}</em>like</a>
			</div>
			<!-- /粉丝 -->
			<!-- 列表 -->
			<div class="user-list">
				<div class="lis-tab clear">
					<a href="#" class="item current">videos<em class="num">{{videoList.length}}</em></a>
					<a href="#" class="item">like<em class="num">0</em></a>
				</div>
				<div class="list-con clear">
					<a href="#" class="list-item" v-for="(item, index) in videoList">
						<span class="lis-vid"><img :src="videoImgs[index]" alt=""></span>
						<em class="like-num">{{item.ups}}</em>
					</a>
				</div>
				<div class="no-more">no more~</div>
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

	import portrait1 from "../assets/img/portrait1.jpg"
	import portrait2 from "../assets/img/portrait2.jpg"
	import portrait3 from "../assets/img/portrait3.jpg"

	import EOS from 'eosjs'

	import config from './config'

	export default {
		name: 'User',
		data() {
			return {
				isScatter: false,
				isFollow: false,
				owner: "",
				userName: "",
				flag: null,
				desc: "",
				follow: 0,
				fans: 0,
				ups: 0,
				videoList: [],
				videoImgs: [videoImg0, videoImg1, videoImg2, videoImg3, videoImg4, videoImg5],
				portraits: [portrait1, portrait2, portrait3]
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
			this.eosClient = EOS(config.eosConfig);
		},

		mounted() {

			var owner = this.$route.params.owner;
			if (!owner) {
				owner = config.contractSender;
			}

			this.eosClient.getTableRows(true, config.contractName, owner, "user").then((data) => {

				if (data.rows && data.rows.length) {
					var user = data.rows[0];

					console.log(user);

					this.owner = user.owner;
					this.userName = user.name;
					this.flag = user.flag;
					this.desc = user.desc;
					this.follow = user.follow;
					this.fans = user.fans;
					this.ups = user.ups;

					this.eosClient.getTableRows(true, config.contractName, user.owner, "video").then((data) => {
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
			followUser: function () {
				if (this.isFollow) {
					this.isFollow = false;
				} else {
					this.isFollow = true;
				}
			}
		}
	}

</script>

<style>
	@import "../assets/css/user.css";
</style>