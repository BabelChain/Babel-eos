import Vue from 'vue'
import Router from 'vue-router'
import Index from '@/components/Index'
import Bar from '@/components/Bar'
import DJRank from '@/components/DJRank'
import User from '@/components/User'
import Wallet from '@/components/Wallet'

Vue.use(Router)

export default new Router({
  routes: [
    {
      path: '/',
      name: 'Index',
      component: Index
    },
    {
      path: '/bar',
      name: 'Bar',
      component: Bar
    },
    {
      path: '/DJRank',
      name: 'DJRank',
      component: DJRank
    },
    {
      path: '/User',
      name: 'User',
      component: User
    },
    {
      path: '/Wallet',
      name: 'Wallet',
      component: Wallet
    }
  ]
})
