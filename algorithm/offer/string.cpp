#include <iostream>

using namespace std;

/*
 * 字符串
 */
class Solution{
public:
	/*
	 * 38
	 * 字符串的排列
	 * 输入一个字符串,按字典序打印出该字符串中字符的所有排列。
	 * 例如输入字符串abc,则打印出由字符a,b,c所能排列出来的所有字符串
	 * abc,acb,bac,bca,cab和cba。
	 *
	 * 输入一个字符串,长度不超过9(可能有字符重复),字符只包括大小写字母。
	 */
	vector<string> Permutation(string str) {
		vector<string> array;
        if(str.size() == 0)
        	return array;
		Permutation(array,str,0);
		//sort(array.begin(),array.end());
		return array;
    }
    void Permutation(vector<string> &array,string str,int begin){
    	if(begin == str.size()-1)
    		array.push_back(str);
    	for(int i = begin; i <= str.size()-1; ++i ){
    		if(i!=begin && str[i] == str[begin]) //重复字符跳过
    			continue;
    		swap(str[i],str[begin]);
    		Permutation(array,str,begin+1); //遍历后面的字符
    		swap(str[i],str[begin]);  //为了防止重复的情况，还需要将begin处的元素重新换回来
    	}
    }

    /*
     * 50
     * 字符流中第一个不重复的字符
     * 请实现一个函数用来找出字符流中第一个只出现一次的字符。
     * 例如，当从字符流中只读出前两个字符"go"时，
     * 第一个只出现一次的字符是"g"。当从该字符流中读出前六个字符“google"时，
     * 第一个只出现一次的字符是"l"。
     * 如果当前字符流没有存在出现一次的字符，返回#字符。
     *
     * 使用关联容器map和unordered_map或实现一个简单的哈希表
     * 一个字符占8位，因此不会超过256个，可以申请一个256大小的数组来
     * 实现一个简易的哈希表。
     */
    int *hashtable = new int[256];
    vector<char> vec;
    //Insert one char from stringstream
	void Insert(char ch)
    {
    	vec.push_back(ch);
    	hashtable[ch]++;
    }
    //return the first appearence once char in current stringstream
    char FirstAppearingOnce()
    {
    	for(int i = 0; i < vec.size(); i++){
    		if(hashtable[vec[i]] == 1)
    			return vec[i];
    	}
    	return '#';
    }

    /*
     * 20
     * 表示数值的字符串
     * 请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。
     * 例如，字符串"+100","5e2","-123","3.1416"和"-1E-16"都表示数值。 
     * 但是"12e","1a3.14","1.2.3","+-5"和"12e+4.3"都不是。
     */
    bool isNumeric(char* string)
    {
        int len=strlen(string);
        int i=0,dot=0,nume=0,num=0;
        if(len==0)
            return true;
        if(string[0]=='+'||string[0]=='-')
            i++;
       while(i<len){
            if(string[i]>='0'&&string[i]<='9'){
                i++;
                num=1;
            }
            else if(string[i]=='.'){
                if(nume>0)
                    return false;
                dot++;
                i++;
            }
            else if(string[i]=='e' ||string[i]=='E'){
                if(nume>0 || num==0)
                    return false;
                nume++;
                i++;
                if(string[i]=='-'||string[i]=='+')
                    i++;
                if(string[i]=='\0')
                    return false;
            }
            else
                return false;
                   
        }
        if(dot>1 ||nume>1)
            return false;
        return true;
    }

    /*
     * 58
     * 左旋转字符串
     * 对于一个给定的字符序列S，请你把其循环左移K位后的序列输出。
     * 例如，字符序列S=”abcXYZdef”,要求输出循环左移3位后的结果，
     * 即“XYZdefabc”。
     */
    string LeftRotateString(string str, int n) {
        int len = str.length();
        if(len == 0)
            return "";
        n = n % len;
        str += str;
        return str.substr(n,len);
    }

    /*
     * 翻转单词顺序咧
     * 输入一个英文句子，翻转句子中单词的顺序，但单词内字符的顺序不变。
     * 为简单起见，标点符号和普通字母一样处理。
     * 如理输入字符串"I am a student."则输出"student. a am I"
     */
    string ReverseSentence(string str) {
        string res = "",tmp = "";
        for(int i = 0;i<int(str.size());++i){
            if(str[i] == ' '){
                res = " " + tmp + res;
                tmp = "";
            }else{
                tmp += str[i];
            }
        }
        if(tmp.size())
            res = tmp+res;
        
        return res;
    }

	/*
	 * 19
	 * 正则表达式的匹配
	 * 请实现一个函数用来匹配包括'.'和'*'的正则表达式。
	 * 模式中的字符'.'表示任意一个字符，而'*'表示它前面的字符可以出现任意次（包含0次）。 
	 * 在本题中，匹配是指字符串的所有字符匹配整个模式。
	 * 例如，字符串"aaa"与模式"a.a"和"ab*ac*a"匹配，但是与"aa.a"和"ab*a"均不匹配
    
     * 思路：只有当模式串和字符串同时等于\0，才可以认为两个串匹配。
     * 在匹配中，对于每个位的匹配可以分为三种情况
     * 1、（相应位匹配||模式串为.&&字符串不是\0）&&模式串下一位是*
     * 2、（相应位匹配||模式串为.&&字符串不是\0）&&模式串下一位不是*
     * 3、相应位不匹配&&（模式位不为.||字符串是\0）
     * 对应1，最复杂。分为*取0，*取1，*>=2三种情况。
     * 取0对应跳过当前匹配位，继续寻找patter的下一个匹配位，str不变，pattern+2
     * 取1对应当前匹配位算一次成功匹配，str+1，pattern+2
     * 取>=2对应一次成功匹配，继续匹配字符串的下一位是否匹配，str+1，pattern不变
     * 三者取或。即只要有一种情况能匹配成功认为字符串就是匹配成功的。
     * 对应2，相当于一次成功匹配，str+1，pattern+1
     * 对应3，匹配失败，直接返回false
	 */
    bool match(char* str, char* pattern)
    {
        if(str==NULL||pattern==NULL)
            return false;
        return matchCore(str,pattern);
    }
    bool matchCore(char* str, char* pattern)
    {
        if(*str=='\0'&&*pattern=='\0')
            return true;
        if(*str!='\0'&&*pattern=='\0')
            return false;
        if(*(pattern+1)=='*')
        {
            if(*pattern==*str||(*pattern=='.'&&*str!='\0'))
            /*
                matchCore(str,pattern+2):模式串未匹配
                matchCore(str+1,pattern):模式串已经匹配成功，尝试匹配下一个字符串
                matchCore(str+1,pat+2)：模式串已经成功匹配，并且不匹配下一个字符串内容  
                注意这里 matchCore(str+1,pat+2)重复考虑了（代码中已经去除），谢谢@chlq的指出 
            */
                return matchCore(str+1,pattern)||matchCore(str,pattern+2);
            else
                return matchCore(str,pattern+2);
        }
        if(*str==*pattern||(*pattern=='.'&&*str!='\0'))
            return matchCore(str+1,pattern+1);
        return false;
    }
	
}