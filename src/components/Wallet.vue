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
			<div class="rank-tab clear">
				<a href="#" :class="tab == 'balance'?'item current':'item'" @click="toggleTab()">余额</a>
				<a href="#" :class="tab == 'coupon'?'item current':'item'" @click="toggleTab()">卡券</a>
			</div>
			<div class="balance" v-if="tab == 'balance'">
				<div class="my-bal">
					<div class="bal-num">
						<span class="img"><img src="../assets/images/balance.png" alt=""></span>
						<span class="txt">¥<em class="txt-em">100.00</em></span>
					</div>
					<a href="#" class="recharge">充值</a>
				</div>
				<div class="bal-det">
					<div class="record">
						<div class="rec-det">
							<span class="rec-img rec"></span>
							<span class="rec-txt">
								<span class="s-name">&nbsp;</span>
								<span class="t-det">成功充值100元</span>
							</span>
						</div>
						<div class="time">5.12 11:23:33</div>
					</div>
					<div class="record">
						<div class="rec-det">
							<span class="rec-img con"></span>
							<span class="rec-txt">
								<span class="s-name">店铺名称</span>
								<span class="t-det">消费100元</span>
							</span>
						</div>
						<div class="time">5.12 11:23:33</div>
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
export default {
  name: 'Wallet',
  data () {
    return {
      tab : "balance",
    }
  },

  created (){

  },

  mounted () {

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