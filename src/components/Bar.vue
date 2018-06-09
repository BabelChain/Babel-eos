<template>
	<div class="w750">
		<header>
			<div class="header-box">
				<a href="javascript:window.history.back();" class="header-img tal"><img src="../assets/images/back.png" alt=""></a>
				<p class="header-txt">酒吧</p>
				<a href="#" class="header-img tar"></a>
			</div>
		</header>
		<div class="bar">
			<div class="bar-msg">
				<div class="bar-bg"><img src="../assets/img/index-img02.jpg" alt=""></div>
				<a href="#" class="res-seat" @click="order()">订座</a>
				<div class="bar-img">
					<span class="img"><img src="../assets/img/user-bg.jpg" alt=""></span>
					<span class="name">{{bar.name}}</span>
				</div>
			</div>
			<div class="bar-score clear">
				<span class="item">
					<em class="img"><img src="../assets/images/foot-img-like.png" alt=""></em>
					<span class="txt">评分&nbsp;&nbsp;{{bar.grade}}</span>
				</span>
				<span class="item">
					<em class="img">&#65509;</em>
					<span class="txt">返利&nbsp;&nbsp;{{bar.rebate}}</span>
				</span>
			</div>
			<div class="bar-int">{{bar.brief}}</div>
			<div class="bar-address">
				<p class="tit">地址：</p>
				<p class="txt address">{{bar.address}}<img src="../assets/images/local.png" alt=""></p>
			</div>
			<div class="bar-star">
				<p class="tit">艺人：</p>
				<div class="star-list clear">
					<a href="#" class="item">
						<span class="img"><img src="../assets/images/head-default.png" alt=""></span>
						<span class="txt">明星名字</span>
					</a>
					<a href="#" class="item">
						<span class="img"><img src="../assets/images/head-default.png" alt=""></span>
						<span class="txt">明星名字</span>
					</a>
					<a href="#" class="item">
						<span class="img"><img src="../assets/images/head-default.png" alt=""></span>
						<span class="txt">明星名字</span>
					</a>
				</div>
			</div>
			<div class="bar-com">
				<a href="#" class="item" @click="grade()" :style="bar.isGrade?'background: #aaa;':''">
					<span v-if="!bar.isGrade"><i class="icon"><img src="../assets/images/small-like.png" alt=""></i>评分</span>
					<span v-else>已评分</span>
				</a>
				<a href="#" class="item"><b class="img">+</b>推荐</a>
			</div>
		</div>
	</div>
</template>

<script>
export default {
  name: 'Bar',
  data () {
    return {
      bar: {
      	id: "1",
      	logo: "",
      	name: "苏荷酒吧",
      	grade: "5.0",
      	rebate: 2.5,
      	brief: "酒吧已成为深圳人休闲必去的地方，是青春和个性的聚集地，那里的酒吧老板大多都是很年轻的新人类，所营造的酒吧氛围不论是热烈还是沉静，都能让人从中找到年轻的感觉",
      	address: "深圳笋岗西路3001号市政设计大厦2楼",
      	isGrade: false
      }
    }
  },

  created () {

  },

  mounted () {

  },

  methods: {
  	order: function(){

  	},

  	grade: function(){
  		
  	}
  }
}

</script>

<style scoped>
@import "../assets/css/bar.css";
</style>