<template>
	<div class="w750">
		<div class="index">
			<!-- 顶部 -->
			<div class="index-top clear">
				<a href="#" class="top-head">
					<router-link to="/user">
						<span class="h-img"><img src="../assets/images/head-default.png" alt=""></span>
					</router-link>
					<em class="add-friend" v-if="!video.current.user" @click="followUser()">+</em>
				</a>
			</div>
			<!-- /顶部 -->
			<div class="video-player">
				<div class="video-control-btns">

					<span @click="playVedio()" v-show="!isPlay" title="play/pause" class="play-or-pause"></span>
					<span @click="previousVideo()" v-show="isHasPrevious" title="previous" class="previous"></span>
					<span @click="nextVideo()" v-show="isHasNext" title="next" class="next"></span>
				</div>
				<video id="videojs-panorama-player" class="video-js vjs-default-skin vjs-big-play-centered" crossorigin="anonymous">
				</video>
			</div>
			<div class="video-info">
				<!-- 视频信息 -->
				<div class="info-box">
					<div class="info-left">
						<div class="tag"><a href="#" class="item">标签1</a><a href="#" class="item">标签2</a></div>
						<div class="activity">
							<a href="#" class="item">
								<!-- <router-link to="/djrank"> --><em class="item-em">#</em>百大Dj年度投票排行榜<!-- </router-link> -->
							</a>
						</div>
						<a href="#" class="user-name">@{{video.current.userName}}</a>
						<p class="video-txt">{{video.current.description}}</p>
					</div>
					<div class="info-right">
						<router-link to="/bar">
							<a href="#" class="song-img"><img src="../assets/images/song-default.png" alt=""></a>
							<a href="#" class="song-name">夜色酒吧</a>
						</router-link>
					</div>
				</div>
				<!-- /视频信息 -->

				<!-- 底部 -->
				<div class="index-foot">
					<div class="foot-box clear">
						<a href="#" class="item like" @click="like()">
							<span class="item-span">
								<img v-if="video.current.isUps" src="../assets/images/foot-img-liked.png" alt="">
								<img v-else src="../assets/images/foot-img-like.png" alt="">
						    </span>
							<span class="item-txt">{{video.current.ups}}</span>
						</a>
						<a href="#" class="item comment" @click="toggleShowComment()">
							<span class="item-span"><img src="../assets/images/foot-img-amount.png" alt=""></span>
							<span class="item-txt">{{video.current.balance.toFixed(2)}}</span>
						</a>
						<a href="#" class="item release">
							<span class="item-span"><img src="../assets/images/foot-img-release.png" alt=""></span>
						</a>
						<router-link to="/user">
							<a href="#" class="item my">
								<span class="item-span"><img src="../assets/images/foot-img-my.png" alt=""></span>
								<span class="item-txt">我的</span>
							</a>
						</router-link>
						<a href="#" class="item share" @click="openInviteLink()">
							<span class="item-span"><img src="../assets/images/foot-img-share.png" alt=""></span>
							<span class="item-txt">{{video.current.share}}</span>
						</a>
					</div>
				</div>
				<!-- /底部 -->

				<!-- 评论弹窗 -->
				<!-- 				<transition name="comment-slide">
					<div id="commentDiv" class="pop-comment" transiton="slide" v-show="isShowComment">
						<div class="com-box">
							<div class="tit">
								<p class="com-num">{{video.current.commentCount}}条评论</p>
								<i class="close" @click="toggleShowComment()"></i>
							</div>
							<div class="com-list">
								<div class="list-item">
									<div class="item-img"><img src="../assets/images/head-default.png" alt=""></div>
									<div class="item-txt">
										<p class="name">评论人的姓名</p>
										<p class="txt">评论内容评论内容评论内容评论内容评论内容</p>
										<span class="time">8小时前</span>
									</div>
									<div class="item-like">
										<span class="like-img"></span>
										<span class="like-num">1158</span>
									</div>
								</div>
								<div class="list-item">
									<div class="item-img"><img src="../assets/images/head-default.png" alt=""></div>
									<div class="item-txt">
										<p class="name">评论人的姓名</p>
										<p class="txt">评论内容评论内容评论内容</p>
										<span class="time">8小时前</span>
									</div>
									<div class="item-like liked">
										<span class="like-img"></span>
										<span class="like-num">1158</span>
									</div>
								</div>
								<div class="list-item">
									<div class="item-img"><img src="../assets/images/head-default.png" alt=""></div>
									<div class="item-txt">
										<p class="name">评论人的姓名</p>
										<p class="txt">评论内容评论内容评论内容评论内容评论内容</p>
										<div class="reply">
											<p class="name">回复人姓名</p>
											<p class="txt">回复内容谁谁</p>
										</div>
										<span class="time">8小时前</span>
									</div>
									<div class="item-like">
										<span class="like-img"></span>
										<span class="like-num">1158</span>
									</div>
								</div>
								<div class="list-item">
									<div class="item-img"><img src="../assets/images/head-default.png" alt=""></div>
									<div class="item-txt">
										<p class="name">评论人的姓名</p>
										<p class="txt">评论内容评论内容评论内容评论内容评论内容</p>
										<span class="time">8小时前</span>
									</div>
									<div class="item-like">
										<span class="like-img"></span>
										<span class="like-num">1158</span>
									</div>
								</div>
								<div class="list-item">
									<div class="item-img"><img src="../assets/images/head-default.png" alt=""></div>
									<div class="item-txt">
										<p class="name">评论人的姓名</p>
										<p class="txt">评论内容评论内容评论内容评论内容评论内容</p>
										<span class="time">8小时前</span>
									</div>
									<div class="item-like">
										<span class="like-img"></span>
										<span class="like-num">1158</span>
									</div>
								</div>
							</div>
						</div>
						<div class="com-bot">
							<input type="text" class="write-com" placeholder="说点儿好听的~">
							<a href="#" class="call">@</a>
						</div>
					</div>
				</transition> -->
				<!-- /评论弹窗 -->

			</div>
		</div>
	</div>
</template>

<script>
	import videojs from "video.js"
	import three from "three"
	import videojsPanorama from "videojs-panorama"
	import EOS from 'eosjs'
	import qs from 'qs'
	var eos;

	const EOS_CONFIG = {
		contractName: "babel", //Contract name
		contractSender: "babel.joe", //User executing the contract (should be paired with private key)
		clientConfig: {
			keyProvider: ['5KVuf8b8pePBsjTfYn3X3L3DayK6dftQiV9jfxGbNseiYfBcBYR'], // Your private key
			httpEndpoint: 'http://10.101.2.109:8888' // EOS http endpoint
		}
	}

	export default {
		name: 'Index',
		data() {
			return {
				isScatter: true,
				isPlay: true,
				isHasNext: false,
				isHasPrevious: false,
				isShowComment: false,
				videoPath: "http://10.101.2.109:8080/ipfs/",
				imagePath: "http://10.101.2.109:8080/ipfs/",
				video: {
					currentIndex: 0,
					current: {
						id: null,
						title: "",
						address: "",
						description: "",
						ups: 0,
						share: 0,
						owner: "",
						balance: 0,
						isUps: false,
						userId: "",
						userName: ""
					},
					list: [],
					user: {

					},
					bar: {

					}
				}
			}
		},

		created() {

			//获取推广id ?invite=id
			var inviteid = qs.parse(location.search.slice(1)).invite;
			console.log(inviteid)
			if (inviteid) {
				this.invite = inviteid;
				localStorage.setItem("INVITE" + this.version, inviteid);
			} else {
				inviteid = localStorage.getItem("INVITE" + this.version);
				if (inviteid) {
					this.invite = inviteid;
				}
			}

			const network = {
				blockchain: 'eos',
				host: '10.101.2.109', // ( or null if endorsed chainId )
				port: 8888, // ( or null if defaulting to 80 )
				chainId: 1 || 'cf057bbfb72640471fd910bcb67639c22df9f92470936cddc1ade0e2f2e7dc4f', // Or null 
			}

			var _this = this;

			// document.addEventListener('scatterLoaded', scatterExtension => {
			// 	// Scatter will now be available from the window scope.
			// 	// At this stage the connection to Scatter from the application is 
			// 	// already encrypted. 
			// 	_this.scatter = window.scatter;

			// 	// It is good practice to take this off the window once you have 
			// 	// a reference to it.
			// 	window.scatter = null;

			// 	// If you want to require a specific version of Scatter
			// 	_this.scatter.requireVersion(3.0);
			// 	this.isScatter = true;
			// 	console.log("scatter installed")

			// 	// Set up any extra options you want to use eosjs with. 
			// 	const eosOptions = {};

			// 	// Get a reference to an 'Eosjs' instance with a Scatter signature provider.
			// 	eos = _this.scatter.eos(network, EOS, eosOptions, 'http');

			// 	eos = EOS(
			// 		{
			// 			keyProvider: ['5KVuf8b8pePBsjTfYn3X3L3DayK6dftQiV9jfxGbNseiYfBcBYR'], // 直接提供私钥。后续应该用scatter方案来替换。
			// 			httpEndpoint: 'http://10.101.2.109:8888' // EOS http endpoint
			// 		}
			// 	)

			// });

			eos = EOS(
				{
					keyProvider: ['5KVuf8b8pePBsjTfYn3X3L3DayK6dftQiV9jfxGbNseiYfBcBYR'], // 直接提供私钥。后续应该用scatter方案来替换。
					httpEndpoint: 'http://10.101.2.109:8888' // EOS http endpoint
				}
			)
		},

		mounted() {


			//获取用户信息
			setTimeout(() => {
				eos.getTableRows(true, EOS_CONFIG.contractName, EOS_CONFIG.contractSender, "video").then((data) => {
					console.log(data);
					if (data.rows && data.rows.length) {

						this.video.list = data.rows.map(row => {
							var obj = {
								id: row.id,
								title: row.title,
								address: row.address,
								description: row.description,
								ups: row.ups,
								share: row.share,
								owner: row.owner,
								balance: parseFloat(row.balance.split(" ")[0]),
								isUps: false,
								userId: "",
								userName: ""
							};
							return obj;
						});

						if (this.video.list.length > 1) {
							this.isHasNext = true;
						};

						this.video.current = this.video.list[0];
						this.initVideo(this.videoPath + this.video.current.address, "video/mp4");

						eos.getTableRows(true, EOS_CONFIG.contractName, this.video.current.owner, "user").then((data) => {

							if (data.rows && data.rows.length) {
								var user = data.rows[0];
								console.log(user);
								this.video.current.userId = user.id;
								this.video.current.userName = user.name;
							}

						}).catch((e) => {
							console.error(e);
						});
					}
				}).catch((e) => {
					console.error(e);
				})
			}, 500);

		},

		methods: {

			//初始化视频
			initVideo: function (src, type) {

				//记住vue实例, 以便在videojs视频单击事件中调用
				var vue = this;

				let player = window.player = videojs('videojs-panorama-player', {
					"preload": "auto",
					"autoplay": true,
					"controls": false,
					"loop": true,
					"sources": [
						{
							src: src,
							type: type
						}
					]
				}, function () {
					window.addEventListener("resize", function () {
						var canvas = player.getChild('Canvas');
						if (canvas) canvas.handleResize();
					});
				});

				let videoElement = document.getElementById("videojs-panorama-player");
				let width = videoElement.offsetWidth;
				let height = videoElement.offsetHeight;
				player.width(width), player.height(height);

				player.panorama({
					clickToToggle: false,
					clickAndDrag: true,
					autoMobileOrientation: true,
					initFov: 100,
					callback: function () {
						player.play();
					}
				});

				//视频单击事件
				player.on('click', function () {
					if (vue.isPlay) {
						this.pause();
					} else {
						this.play();
					}
				});

				//视频播放事件
				player.on('play', function () {
					vue.isPlay = true;
				});

				//视频暂停事件
				player.on('pause', function () {
					vue.isPlay = false;
				});
			},

			//播放视频
			playVedio: function () {
				if (!this.isPlay) {
					player.play();
				}
			},

			//暂停视频
			playPause: function () {
				if (this.isPlay) {
					player.pause();
				}
			},

			//上一个视频
			previousVideo: function () {

				if (!this.video.list && !this.video.list.length) {
					return;
				}

				var previous = this.video.currentIndex - 1;
				if (previous >= 0) {
					this.video.currentIndex = previous;

					if (!this.isHasNext) {
						this.isHasNext = true;
					}

					if (this.video.currentIndex === 0) {
						this.isHasPrevious = false;
					}

					this.video.current = this.video.list[previous];
					player.src({
						src: this.videoPath + this.video.current.address,
						type: "video/mp4"
					});
					player.play();
				}
			},

			//下一个视频
			nextVideo: function () {
				if (!this.video.list && !this.video.list.length) {
					return;
				}

				var next = this.video.currentIndex + 1;

				if (next < this.video.list.length) {

					this.video.currentIndex = next;
					if (!this.isHasPrevious) {
						this.isHasPrevious = true;
					}

					if (this.video.currentIndex === (this.video.list.length - 1)) {
						this.isHasNext = false;
					}

					this.video.current = this.video.list[next];
					player.src({
						src: this.videoPath + this.video.current.address,
						type: "video/mp4"
					});
					player.play();
				}
			},

			// 点赞或取消点赞
			like: function () {

				//记住vue实例, 以便在某些回调方法中使用
				var vue = this;

				if (!this.video.current.id) {//no video
					// TODO something
					return;
				}

				if (!vue.video.current.isUps) {//is like yes
					vue.video.current.isUps = true;
					vue.video.current.ups += 1;

					const requiredFields = {
						personal: ['firstname', 'email'],
						location: ['country'],
						accounts: [
							{ blockchain: 'eos', host: '10.101.2.109', port: 8888 },
							{ blockchain: 'eth', chainId: 1 }
						]
					};

					// this.scatter.getIdentity().then(identity => {

					// 	console.log(identity)


					// 	//...
					// }).catch(error => {
					// 	//...
					// });

					eos.contract(EOS_CONFIG.contractName).then((contract) => {
						contract.like(this.video.current.owner, "babel.joe", this.video.current.id, { authorization: ["babel.joe"] }).then((res) => {
							console.log(res)
							vue.video.current.balance += 1;
						}).catch((err) => {
							console.log(err)
						})
					})


				}
			},

			openInviteLink: function () {
				var _this = this;
				_this.inviteLink = location.origin + "?invite=" + this.video.current.userId;

				alert(_this.inviteLink + '    请复制您的邀请链接');
			},

			// 弹出评论窗口
			toggleShowComment: function () {
				if (!this.video.current.id) {//no video
					// TODO something
					return;
				}

				if (this.isShowComment) {
					this.isShowComment = false;

					player.play();//播放视频
				} else {
					this.isShowComment = true;

					player.pause();//暂停视频

					//给弹层设置高度
					setTimeout(function () {
						var commentDiv = document.getElementById("commentDiv");
						var commentDivHeight = commentDiv.offsetHeight;

						var titHeight = commentDiv.querySelectorAll(".tit")[0].offsetHeight;
						var comBotHeight = commentDiv.querySelectorAll(".com-bot")[0].offsetHeight;
						var comList = commentDiv.querySelectorAll(".com-list")[0];

						var comListHeight = commentDivHeight - (titHeight + comBotHeight);
						comList.style = "height:" + comListHeight + "px";
					}, 500);
				}
			},

			//关注当前用户
			followUser: function () {
				//记住vue实例, 以便在某些回调方法中使用
				var vue = this;

			}
		}
	}

</script>

<style>
	@import "video.js/dist/video-js.min.css";
	@import "videojs-panorama/dist/videojs-panorama.min.css";
	@import "../assets/css/index.css";
	.comment-slide-enter-active,
	.comment-slide-leave-active {
		height: 70%;
		transition: all 0.5s;
	}
	
	.comment-slide-enter,
	.comment-slide-leave-active {
		height: 0;
		transition: all 0.5s;
	}
</style>