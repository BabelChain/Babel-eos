<template>
	<div class="w750">
		<header>
			<div class="header-box">
				<router-link :to="{name:'Index'}">
					<a class="header-img tal"><img src="../assets/images/back.png" alt=""></a>
				</router-link>
				<p class="header-txt">club</p>
				<a href="#" class="header-img tar"></a>
			</div>
		</header>
		<div class="bar">
			<div class="bar-msg">
				<div class="bar-bg"><img src="../assets/img/index-img02.jpg" alt=""></div>
				<a href="#" class="res-seat" v-if="isOrder" style="background: #ccc;">reserved</a>
				<a href="#" class="res-seat" @click="order()" v-else>ticketing100.00&nbsp;DJB</a>
				<div class="bar-img">
					<span class="img"><img src="../assets/img/user-bg.jpg" alt=""></span>
					<span class="name">{{userName}}</span>
				</div>
			</div>
			<div class="bar-score clear">
				<span class="item">
					<em class="img"><img src="../assets/images/foot-img-like.png" alt=""></em>
					<span class="txt">star&nbsp;&nbsp;5.0</span>
				</span>
				<span class="item">
					<em class="img">$</em>
					<span class="txt">&nbsp;&nbsp;{{balance + ' ' + symbol}}</span>
				</span>
			</div>
			<div class="bar-int">Since it opened its doors in 2004, Volar has ruled over the Hong Kong nightlife circuit as the city’s coolest club</div>
			<div class="bar-address">
				<p class="tit">add:</p>
				<p class="txt address">Basement, 38-44 D'Aguilar Street, Lan Kwai Fong, Hong Kong<img src="../assets/images/local.png" alt=""></p>
			</div>
			<div class="bar-star">
				<p class="tit">artist：</p>
				<div class="star-list clear">
					<a href="#" class="item">
						<span class="img"><img src="../assets/images/head-default.png" alt=""></span>
						<span class="txt">Avicii</span>
					</a>
					<a href="#" class="item">
						<span class="img"><img src="../assets/images/head-default.png" alt=""></span>
						<span class="txt">Avicii</span>
					</a>
					<a href="#" class="item">
						<span class="img"><img src="../assets/images/head-default.png" alt=""></span>
						<span class="txt">Avicii</span>
					</a>
				</div>
			</div>
			<!-- <div class="bar-com">
				<a href="#" class="item" @click="grade()" :style="bar.isGrade?'background: #aaa;':''">
					<span v-if="!bar.isGrade"><i class="icon"><img src="../assets/images/small-like.png" alt=""></i>评分</span>
					<span v-else>已评分</span>
				</a>
				<a href="#" class="item"><b class="img">+</b>推荐</a>
			</div> -->
		</div>
	</div>
</template>

<script>

import EOS from 'eosjs'
import config from './config'



export default {
  name: 'Bar',
  data () {
    return {
    	isOrder: false,
  		userId: "",
		userName: "",
		follow: 0,
		fans: 0,
		ups: 0,
		balance: 0,
		symbol: "DJB"
    }
  },

  created () {
	  /*const network = {
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
        eos = scatter.eos( network, EOS, eosOptions, 'http' );
        
        })*/

        this.eosClient = EOS(config.eosConfig);
  },

  mounted () {

  	//获取酒吧信息
	this.eosClient.getTableRows(true, config.contractName, "babel.bar", "user").then((data) => {

		if (data.rows && data.rows.length) {
			var user = data.rows[0];

			this.userId = user.id;
			this.userName = user.name;
			this.follow = user.follow;
			this.fans = user.fans;
			this.ups = user.ups;

			var balances = user.balance.split(" ");
			this.balance = parseFloat(balances[0]);
			this.symbol = balances[1];
		}
	}).catch((e) => {
		console.error(e);
	})
  },

  methods: {

  	//订座
  	order: function(){

  		if(window.confirm("are u confirm，it will send 100 DJB token to club？")){
  			var bar_name = "babel.bar"
			var user_name = "babel.joe"
			var money = "100.0000 DJB"
			var inviter = localStorage.getItem("INVITE") || "";
			console.log(inviter);

			if(inviter){
	    		this.balance += 80;
	    		user_name = "babel.dj";
	    	}else{
	    		this.balance += 100;
	    	}
	        
	        this.isOrder = true;

			this.eosClient.contract(config.contractName).then((contract) => {
			    contract.booking(bar_name, user_name, money, inviter, { authorization: [user_name] }).then((res) => {
			    	console.log(res);
			    }).catch((err) => {
			        console.log(err);
			    })
			})

			localStorage.removeItem("INVITE");
  		}
  	}
  }
}

</script>

<style scoped>
@import "../assets/css/bar.css";
</style>