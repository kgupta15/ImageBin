/**
* @Author: daemonslayer
* @Date:   2017-01-16T15:37:33+05:30
* @Last modified by:   daemonslayer
* @Last modified time: 2017-01-16T15:37:45+05:30
*/



#pragma once


#ifndef UTIL_H_
#define UTIL_H_

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <set>


enum Color {
    NONE = 0,
    BLACK, RED, GREEN,
    YELLOW, BLUE, MAGENTA,
    CYAN, WHITE
};


static std::string set_color(Color foreground = NONE, Color background = NONE) {
  std::stringstream s;
  s << "\033[";
  if (!foreground && ! background){
    s << "0"; // reset colors if no params
  }

  if (foreground) {
    s << 29 + foreground;
    if (background) s << ";";
  }

  if (background) {
    s << 39 + background;
  }

  s << "m";
  return s.str();
}

std::ostream& bold_on(std::ostream& os) {
  return os << "\e[1m";
}

std::ostream& bold_off(std::ostream& os) {
  return os << "\e[0m";
}



#define __ERR_SIG__ std::cout << set_color(RED) << "[#] HELP: Fuckup Happened Here!!!" << std::endl
#define __ERR_SIG_L__ std::cout << set_color(RED) << "[#] HELP: Fuckup Happened on Line " << __LINE__ << "!!!" <<set_color(NONE) << std::endl
#define __ERR_SIG_B__ std::cout << bold_on << set_color(RED) << "[#] HELP: Fuckup Happened on Line " << __LINE__ << "!!!" << set_color(NONE) << bold_off << std::endl
#define __PLINE__ std::cout << set_color(RED) << __LINE__ << set_color(NONE)<< std::endl

void props(std::set<std::pair< std::string, double> > prop_set) {
  std::set< std::pair<std::string, double> >::iterator itr;
  std::cout << set_color(GREEN);

  for (itr = prop_set.begin(); itr != prop_set.end(); ++itr) {
    std::cout << itr->first << " : " << itr->second << std::endl;
  }

  std::cout << set_color(NONE);
}


void title(std::string header_str) {
  std::cout << bold_on << set_color(CYAN) << "[#] " << header_str << set_color(NONE) << bold_off << std::endl;
}

void stat_comp(std::string feature) {
  std::cout << bold_on << set_color(BLUE) << "[+] " << feature << " : DONE" << set_color(NONE) << bold_off << std::endl;
}

void test(std::string test_str) {
  std::cout << bold_on << set_color(YELLOW) << "[$] " << test_str << " : TESTING" << set_color(NONE) << bold_off << std::endl;
}

void logger(std::string log_str) {

}

void err_report(std::string err_str) {
  std::cout << bold_on << set_color(RED) << "[-] " << err_str << " : ERROR" << set_color(NONE) << bold_off << std::endl;
}


#endif // UTIL_H_
