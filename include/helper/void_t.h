/*
 * void_t.h
 *
 *  Created on: Apr 4, 2016
 *      Author: vogt
 */

#ifndef VOID_T_H_
#define VOID_T_H_

/**
 * In C++11 it should be possible to do SFINAE class selection with
 *    template <typename... Ts> using void_t = void;
 * However g++-4.x interprets this differently, see description and workaround
 *    http://stackoverflow.com/a/35754473/5085250
 *
 * Workaround tested with g++-4.8.3, g++-4.9.0, g++-5.3.1, g++-6.0.0
 */


namespace void_details
{
    template <typename... > struct make_void { using type = void; };
}

template<typename... T> using void_t = typename void_details ::make_void<T...>::type;



#endif /* INCLUDE_HELPER_VOID_T_H_ */
