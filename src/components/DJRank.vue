<template>
	<div class="w750">
		<header>
			<div class="header-box">
				<a href="javascript:window.history.back();" class="header-img tal"><img src="../assets/images/back.png" alt=""></a>
				<p class="header-txt">DJ榜单</p>
				<a href="#" class="header-img tar"></a>
			</div>
		</header>
		<div class="DJ-rank">
			
			<div class="rank-tab clear">
				<a href="#" :class="tab=='day'?'item current':'item'" @click="toggleTab()">今日排行</a>
				<a href="#" :class="tab=='year'?'item current':'item'" @click="toggleTab()">年度投票</a>
			</div>

			<div class="rank-list year-rank">

				<div class="list-item clear" v-for="(item, index) in list">
					<span :class="index == 0?'rank the-first':'rank'">No.{{index + 1}}</span>
					<div class="DJ-img">
						<span class="img">
							<img src="../assets/images/head-default.png" alt="">
							<em class="first-icon"><img src="../assets/images/king.png" alt=""></em>
						</span>
						<span class="name">{{item.userName}}</span>
					</div>
					<div class="DJ-msg">
						<p class="des">{{item.brief}}</p>
						<p class="like-watch">点赞<span class="num">{{item.likeCount}}</span>次，观看<span class="num">{{item.viewCount}}</span>次</p>
					</div>
					<div class="tickets" v-if="tab=='year'">
						<a href="#" :class="item.isVote?'disbtn':'btn'" @click="vote(index)">{{item.isVote?'已投票':'投票'}}</a>
						<span class="num">{{item.voteCount}}</span>
					</div>
				</div>
			</div>
			<!-- /年度投票 -->
		</div>
	</div>
</template>

<script>
export default {
  name: 'DJrank',
  data () {
    return {
      tab: "day",
      list: [
      	{
      		userId: "1",
      		userName: "DJ妞妞",
      		portrait: "",
      		brief: "我是一名DJDJDJDJDJDJDJDJDJDJDJ, 是一名很厉害的DJ",
      		likeCount: 500,
      		viewCount: 20,
      		voteCount: 10,
      		isVote: false
      	}
      ]
    }
  },

  created () {

  },

  mounted () {

  },

  methods: {

  	//切换Tab
  	toggleTab: function(){
  		if(this.tab == "day"){
  			this.tab = "year"
  		}else{
  			this.tab = "day"
  		}
  	},

  	//投票
  	vote: function(index){
  		if(!this.list[index].isVote){
  			this.list[index].isVote = true;
  		}
  	}
  }
}

</script>

<style scoped>
@import "../assets/css/DJ-rank.css";
</style>