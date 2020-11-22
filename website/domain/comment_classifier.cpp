#include"comment_classifier.h"

using namespace std;

pair< string,pair<double,double> > CommentClassifier::parse_csv(string line)
{
    int last_comma=-1,first_comma=-1;
    for(int i=line.size()-1;0<=i;i--)
        if(line[i]==',')
        {
            if(last_comma==-1)
                last_comma=i;
            else if(first_comma==-1)
                first_comma=i;
        }
    double first=stod( line.substr(first_comma+1,last_comma-first_comma-1) );
    double second=stod( line.substr(last_comma+1,line.size()-last_comma-1) );
    return make_pair(line.substr(0,first_comma),make_pair(first,second));
}

vector< pair<string,pair<double,double> > > CommentClassifier::read_train_csv(string trainDataPath)
{
    vector< pair<string,pair<double,double> > > result;
    ifstream fread;
    fread.open(trainDataPath);
    if( !fread.good() )
        throw NotFound();
    string line;
    bool first_line=true;
    while( getline(fread,line) )
    {
        if(first_line)
        {
            first_line=false;
            continue;
        }
        result.push_back( parse_csv(line) );
    }
    return result;
}

void CommentClassifier::train(string trainDataPath, string classProbabilitiesPath)
{
    vector< pair< string,pair<double,double> > > data=read_train_csv(trainDataPath);
    for(int i=0;i<data.size();i++)
    {
        p_word_exists_in_good_cm[data[i].first]=data[i].second.first;
        p_word_exists_in_bad_cm[data[i].first]=data[i].second.second;
    }
    ifstream pread;
    pread.open(classProbabilitiesPath);
    if( !pread.good() )
        throw NotFound();
    string line;
    getline(pread,line);
    p_good_comment=stod(line);
    p_bad_comment=1.0-p_good_comment;
}

void CommentClassifier::parse_words(string comment, int start, vector<string>& words)
{
    if(start >= comment.size())
        return;
    while(comment[start]==' ')
        start++;
    if(start >= comment.size())
        return;
    for(int i=start;i<comment.size();i++)
        if(comment[i]==' ')
        {
            words.push_back( comment.substr(start,i-start) );
            return parse_words(comment, i, words);
        }
    words.push_back( comment.substr(start,comment.size()-start) );
    return;
}

bool CommentClassifier::classify_comment(string comment)
{
    vector<string> words;
    parse_words(comment,0,words);
    double log_p_good=0.0;
    double log_p_bad=0.0;
    for(int i=0;i<words.size();i++)
    {
        log_p_good+=log10( p_word_exists_in_good_cm[words[i]] );
        log_p_bad+=log10( p_word_exists_in_bad_cm[words[i]] );
    }
    double p_good=pow(10.0,log_p_good) * p_good_comment;
    double p_bad=pow(10.0,log_p_bad) * p_bad_comment;
    if(p_good > p_bad)
        return false;
    if(p_good < p_bad)
        return true;
    if(p_good_comment > p_bad_comment)
        return false;
    return true;
}

void CommentClassifier::test(string testDataPath)
{
    ifstream tread;
    tread.open(testDataPath);
    string line;
    int correct_detected_appropriate_comments=0;
    int all_appropriate_comments=0;
    int detected_appropriate_comments=0;
    int correct_detected=0;
    int all_comments=0;
    bool first_line=true;
    while( getline(tread,line) )
    {
        if(first_line)
        {
            first_line=false;
            continue;
        }
        all_comments++;
        string comment=line.substr(0,line.size()-2);
        int c_class=line[line.size()-1]-'0';
        bool prediction=classify_comment(comment);
        if( !c_class )
            all_appropriate_comments++;
        if( !c_class && !prediction )
        {
            correct_detected_appropriate_comments++;
            correct_detected++;
        }
        if( c_class && prediction )
            correct_detected++;
        if( !prediction )
            detected_appropriate_comments++;
    }
    ofstream evaluate;
    evaluate.open("output.txt");
    double recall=(double)( (double)correct_detected_appropriate_comments/(double)all_appropriate_comments )*100.0;
    double precision=(double)( (double)correct_detected_appropriate_comments/(double)detected_appropriate_comments )*100.0;
    double accuracy=(double)( (double)correct_detected/(double)all_comments )*100.0;
    evaluate << "Recall: "+to_string(recall) << endl;
    evaluate << "Precision: "+to_string(precision) << endl;
    evaluate << "Accuracy: "+to_string(accuracy) <<endl;
    evaluate.close();
    return;
}
