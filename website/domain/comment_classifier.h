#ifndef __COMMENT_CLASSIFIER_H_
#define __COMMENT_CLASSIFIER_H_

#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<fstream>
#include<sstream>
#include<cmath>
#include<stdlib.h>
#include"exceptions.h"

class CommentClassifier {
public:
    CommentClassifier() {};
    CommentClassifier(std::string trainDataPath, std::string classProbabilitiesPath)
                {train(trainDataPath,classProbabilitiesPath);} ;
    void train(std::string trainDataPath, std::string classProbabilitiesPath);
    void test(std::string testDataPath);
    bool classify_comment(std::string comment);
private:
    std::pair< std::string,std::pair<double,double> > parse_csv(std::string line);
    std::vector< std::pair<std::string,std::pair<double,double> > > read_train_csv(std::string dataPath);
    void parse_words(std::string comment, int start, std::vector<std::string>& words);

    std::unordered_map<std::string,double> p_word_exists_in_bad_cm;
    std::unordered_map<std::string,double> p_word_exists_in_good_cm;
    double p_good_comment;
    double p_bad_comment;
};

#endif
