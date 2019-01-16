//Instructions: To avoid library issues, run it in https://repl.it/
#include <bits/stdc++.h>

using namespace std;

int main(){
    string s="pwwkew";
    cout<<"Enter your string: ";
    cin>>s;
    map<char, int> m; //position of last seen of character char
    int answer=0;
    int current=0;
    for(int i=0; i<s.length(); i++){
        if(m.find(s[i]) == m.end()){
            m[s[i]]=i;
            current++;
        }else{
            if(i-current<=m[s[i]]){
                current=i-m[s[i]];
            } else current++;
            m[s[i]]=i;
        }
        //cout<<s[i]<<": "<<m[s[i]]<<endl;
        if(answer<current) answer=current;
    }
    cout<<"The answer is "<<answer;
    return 0;
}