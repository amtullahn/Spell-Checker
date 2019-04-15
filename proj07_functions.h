#pragma once 

#include <algorithm>
#include <fstream>
#include <set>
#include <string>

const std::string letters = "abcdefghijklmnopqrstuvwxyz";

void deletes(const std::string &word, std::set<std::string> &result);

void inserts(const std::string &word, std::set<std::string> &result);

void transposes(const std::string &word, std::set<std::string> &result);

void replaces(const std::string &word, std::set<std::string> &result);

void read_words(std::string fname, std::set<std::string> &result);


void find_completions(const std::string &word,
                      const std::set<std::string> &word_list,
                      std::set<std::string> &result) ;

void find_corrections(const std::string &word,
                      std::set<std::string> &result) ;

void find_2step_corrections(const std::string &word,
                            std::set<std::string> &result) ;

void find_reasonable_corrections(const std::set<std::string> &possibles,
                                 const std::set<std::string> &word_list,
                                 std::set<std::string> &result) ;

std::string print_set(const std::set<std::string> &s) ;


