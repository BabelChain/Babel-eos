<template>
	<div class="w750">
		<header>
			<div class="header-box">
				<a href="javascript:window.history.back();" class="header-img tal"><img src="../assets/images/back.png" alt=""></a>
				<p class="header-txt">钱包</p>
				<a href="#" class="header-img tar"></a>
			</div>
		</header>
		<div class="wallet">
			<!-- 余额 -->
<!-- 			<div class="rank-tab clear">
				<a href="#" :class="tab == 'balance'?'item current':'item'" @click="toggleTab()">余额</a>
				<a href="#" :class="tab == 'coupon'?'item current':'item'" @click="toggleTab()">卡券</a>
			</div> -->
			<div class="balance" v-if="tab == 'balance'">
				<div class="my-bal">
					<div class="bal-num">
						<span class="img"><img src="../assets/images/balance.png" alt=""></span>
						<span class="txt"><em class="txt-em">{{balance.toFixed(2)}}</em></span>
					</div>
					<a href="#" class="recharge">充值</a>
				</div>
				<div class="bal-det">
					<div class="record" v-for="item in logs">
						<div class="rec-det">
							<span :class="item.type == 1?'rec-img rec':'rec-img con'"></span>
							<span class="rec-txt">
								<span class="t-det">{{item.description}}</span>
							</span>
						</div>
						<div class="time">{{item.quantity}}</div>
					</div>
				</div>
			</div>
			<!-- /余额 -->

			<div class="coupon" v-if="tab == 'coupon'">
				<div class="cou-list clear">
					<div class="img"><img src="../assets/images/coupon.png" alt=""></div>
					<div class="txt">
						<p class="place">店铺名称</p>
						<p class="con">酒水8折</p>
					</div>
				</div>
				<div class="cou-list clear">
					<div class="img"><img src="../assets/images/coupon.png" alt=""></div>
					<div class="txt">
						<p class="place">店铺名称</p>
						<p class="con">酒水8折</p>
					</div>
				</div>
			</div>
			<!-- /余额 -->
		</div>
	</div>
</template>

<script>

import EOS from 'eosjs'
var eos;

const EOS_CONFIG = {
	contractName: "babel.user", //Contract name
	contractSender: "babel.joe", //User executing the contract (should be paired with private key)
	clientConfig: {
		keyProvider: ['5KVuf8b8pePBsjTfYn3X3L3DayK6dftQiV9jfxGbNseiYfBcBYR'], // Your private key
		httpEndpoint: 'http://10.101.2.109:8888' // EOS http endpoint
	}
}

export default {
  name: 'Wallet',
  data () {
    return {
      tab : "balance",
      userId: "",
      userName: "",
      balance: 0,
      logs:[]
    }
  },

  created (){
  	const network = {
		blockchain: 'eos',
		host: '10.101.2.109', // ( or null if endorsed chainId )
		port: 8888, // ( or null if defaulting to 80 )
		chainId: 1 || 'cf057bbfb72640471fd910bcb67639c22df9f92470936cddc1ade0e2f2e7dc4f', // Or null 
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
	});
  },

  mounted () {
	
	setTimeout( () => {
		eos.getTableRows(true, EOS_CONFIG.contractName, "babel.joe", "user").then((data) => {

			if(data.rows && data.rows.length){
				var user = data.rows[0];
				console.log(user);
				this.userId = user.id;
				this.userName = user.name;
				this.balance = parseFloat(user.balance.split(" ")[0]);

				eos.getTableRows(true, EOS_CONFIG.contractName, user.owner, "log").then((data) => {
				    this.logs = data.rows;
				    console.log( this.logs);
				}).catch((e) => {	
				    console.error(e);
				})
			}

		}).catch((e) => {
			console.error(e);
		});
	}, 500);
  },

  methods: {
  	toggleTab: function(){
  		if(this.tab == "balance"){
  			this.tab = "coupon";
  		} else {
  			this.tab = "balance";
  		}
  	}
  }
}

</script>

<style scoped>
@import "../assets/css/wallet.css";
</style>