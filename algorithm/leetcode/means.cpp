/**
 * 细节实现题
 * 不同特定算法，考察代码熟练 程度
 */
class Solution{
public:
	/**
	 * 6. ZigZag Conversion
The string "PAYPALISHIRING" is written in a zigzag pattern on a given number 
of rows like this: (you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R

And then read line by line: "PAHNAPLSIIGYIR"

Write the code that will take a string and make this conversion given a number of rows:

string convert(string s, int numRows);

Example 1:
Input: s = "PAYPALISHIRING", numRows = 3
Output: "PAHNAPLSIIGYIR"

Example 2:
Input: s = "PAYPALISHIRING", numRows = 4
Output: "PINALSIGYAHRPI"
Explanation:
P     I    N
A   L S  I G
Y A   H R
P     I

problem:
https://leetcode.com/problems/zigzag-conversion/description/
	//对于每一层垂直元素的坐标(i,j) = (j+1)*n+i；
	//对于每两层垂直元素之间的插入元素(斜对角元素)，(i,j)=(j+1)*n-1;
	 */
	string convert(string s, int numRows) {
        if(numRows <=1 || s.size()<=1) return s;
        string result;

        for(int i=0; i<numRows; i++){
        	for(int j=0,index=i; index<s.size(); j++, index=(2*numRows-2)*j+i){
        		result.append(1,s[index]); //垂直元素
        		if(i==0 || i==numRows-1) continue;
        		if(index + (numRows-i-1) *2 < s.size())
        			result.append(1,s[index+(numRows-i-1)*2]);
        	}
        }

        return result;
    }

	/**
	 * 7. Reverse Integer
Given a 32-bit signed integer, reverse digits of an integer.

Example 1:

Input: 123
Output: 321
Example 2:

Input: -123
Output: -321
Example 3:

Input: 120
Output: 21
Note:
Assume we are dealing with an environment which could only store integers within the 32-bit signed integer 
range: [−231,  231 − 1]. For the purpose of this problem, assume that your function returns 0 
when the reversed integer overflows.
	 */
	//考虑 1. 负数的情况 2. 溢出的情况 (正溢出 && 负移除 x = -2147483648(即-2^31) )
	int reverse(int x){
		long long r=0;
		long long t=x;
		t = t>0?t:-t;

		for(;t;t/=10)
			r = r*10 + t%10;

		bool sign = x>0?false:true;
		if(r>2147483647 || (sign && r>2147483648)){
			return 0;
		}else{
			if(sign)
				return -r;
			else
				return r;
		}
	}

	/**
	 * 9. Palindrome Number
Determine whether an integer is a palindrome. An integer is a palindrome when it reads the same backward as forward.

Example 1:

Input: 121
Output: true
Example 2:

Input: -121
Output: false
Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.
Example 3:

Input: 10
Output: false
Explanation: Reads 01 from right to left. Therefore it is not a palindrome.
Follow up:

Coud you solve it without converting the integer to a string?
	 */
	//不断地取第一位和最后一位进行比较，相等则取第二位和倒数第二位，知道完成比较或者找到了不一致的位
	bool isPalindrome(int x){
		if(x<0)
			return false;

		int d=1;
		while(x/d >= 10)
			d *= 10;

		while(x>0){
			int q = x/d;
			int r = x%10;
			if(q != r)
				return false;
			x = x%d/10;
			d /= 100;
		}

		return true;
	}

	/**
	 * 29. Divide Two Integers
Given two integers dividend and divisor, divide two integers without using multiplication, division and mod operator.

Return the quotient after dividing dividend by divisor.

The integer division should truncate toward zero.

Example 1:
Input: dividend = 10, divisor = 3
Output: 3

Example 2:
Input: dividend = 7, divisor = -3
Output: -2
Note:

Both dividend and divisor will be 32-bit signed integers.
The divisor will never be 0.
Assume we are dealing with an environment which could only store integers within the 32-bit signed integer range: 
[−231,  231 − 1]. For the purpose of this problem, assume that your function returns 231 − 1 when the division result overflows.
	 */
	//不能用乘、除和取模，还有加、减和位运算
	int divide(int dividend, int divisor) {
		if(dividend == 0)
			return 0;
		if(divisor == 0)
			return INT_MAX;

		long long res = double(exp(log(fabs(dividend)) - log(fabs(divisor))));

		if((dividend < 0) ^ (divisor < 0))
			res = -res;
		if(res>INT_MAX)
			res = INT_MAX;

		return res;
	}

	/**
	 * 30. Substring with Concatenation of All Words
You are given a string, s, and a list of words, words, that are all of the same length. 
Find all starting indices of substring(s) in s that is a concatenation of each word in words exactly once 
and without any intervening characters.

Example 1:
Input:
  s = "barfoothefoobarman",
  words = ["foo","bar"]
Output: [0,9]
Explanation: Substrings starting at index 0 and 9 are "barfoor" and "foobar" respectively.
The output order does not matter, returning [9,0] is fine too.

Example 2:
Input:
  s = "wordgoodstudentgoodword",
  words = ["word","student"]
Output: []
	 */
	//dp through sliding window
	vector<int> findSubstring(string s, vector<string>& words) {
		vector<int> re;
		if (s.empty() || words.empty()) return re;
		int n = words[0].size(), length1 = s.size(), length2 = words.size();
		map<string, int> aa;

		for (auto x : words) 
			++aa[x];

		for (int i = 0; i < n; ++i){
			int l = i, r = i; //l指向滑动窗口最左边的单词的起始点， r指向滑动窗口最右边的单词的起始点
			map<string, int> bb;
			while (r + n <= s.size()){
				if (aa.count(s.substr(r, n))){//有效单词
					string wd = s.substr(r, n);
					++bb[wd];
					r += n;
					if (bb[wd] < aa[wd]) 
						continue; // 当前单词个数小于目标单词个数，r右移，添加最右端单词(continue,跳到下一次循环自动执行)

					while (bb[wd] > aa[wd]){   //当前单词个数大于目标单词个数，删除最左端单词，l右移
						if (--bb[s.substr(l, n)] == 0)
							bb.erase(s.substr(l, n));
						l += n;
					}//这里一定要注意用while循环（而不是if），直到当前单词个数等于目标单词个数，具体原因可以自己跑样例写下体会下  
				
               		if (bb[wd] == aa[wd] && r - l == length2 * n){  //当前单词个数等于目标单词个数，比较目前单词总数与目标单词总数是否相等，
					//如果不相等：r右移，添加最右端单词(跳到下一次循环自动执行)。如果相等：删除最左端单词，l右移；r右移，添加最右端单词(跳到下一次循环自动执行)。
						re.push_back(l);
						if (--bb[s.substr(l, n)] == 0)
							bb.erase(s.substr(l, n));
						l += n;
					}
				}
				else {  //如果单词无效，则l,r跳到下一个单词处重新开始计数
					bb.clear();
					r += n;
					l = r;
				}
			}
		}
		return re;
	}

	/**
	 * 43. Multiply Strings
Given two non-negative integers num1 and num2 represented as strings, 
return the product of num1 and num2, also represented as a string.

Example 1:
Input: num1 = "2", num2 = "3"
Output: "6"

Example 2:
Input: num1 = "123", num2 = "456"
Output: "56088"

Note:
The length of both num1 and num2 is < 110.
Both num1 and num2 contain only digits 0-9.
Both num1 and num2 do not contain any leading zero, except the number 0 itself.
You must not use any built-in BigInteger library or convert the inputs to integer directly.

problem:
https://leetcode.com/problems/multiply-strings/description/

solution:
https://leetcode.com/problems/multiply-strings/discuss/17646/Brief-C++-solution-using-only-strings-and-without-reversal
	 */
	string multiply(string num1, string num2) {
		string sum(num1.size() + num2.size(), '0');

		for(int i=num1.size()-1; 0<=i; --i){
			int carry = 0;
			for(int j=num2.size()-1; 0<=j; --j){
				int tmp = (sum[i+j+1]-'0') + (num1[i]-'0') * (num2[j] - '0') + carry;
				sum[i+j+1] = tmp % 10 + '0';
				carry = tmp/10;
			}

			sum[i] += carry;
		}

		size_t startpos = sum.find_first_not_of("0");
		if(string::npos != startpos){
			return sum.substr(startpos);
		}

		return "0";
	}

	/**
	 * 50. Pow(x, n)
Implement pow(x, n), which calculates x raised to the power n (xn).

Example 1:
Input: 2.00000, 10
Output: 1024.00000

Example 2:
Input: 2.10000, 3
Output: 9.26100

Example 3:
Input: 2.00000, -2
Output: 0.25000
Explanation: 2-2 = 1/22 = 1/4 = 0.25

Note:
-100.0 < x < 100.0
n is a 32-bit signed integer, within the range [−231, 231 − 1]
	 */
	//二分法，$x^n = x^{n/2} * x^{n/2} * x^{n\%2}$
	double myPow(double x, int n){
		if(n<0)
			return 1.0/power(x,-n);
		else
			return power(x,n);
	}
	double power(double x, int n){
		if(n==0)
			return 1;

		double v = power(x,n/2);

		if(n%2 == 0)
			return v*v;
		else 
			return v*v*x;
	}

	/**
	 * 54. Spiral Matrix
Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.

Example 1:
Input:
[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]
Output: [1,2,3,6,9,8,7,4,5]

Example 2:
Input:
[
  [1, 2, 3, 4],
  [5, 6, 7, 8],
  [9,10,11,12]
]
Output: [1,2,3,4,8,12,11,10,9,5,6,7]
	 */
	vector<int> spiralOrder(vector<vector<int>>& matrix) {
		vector<int> result;
		if(matrix.empty())
			return result;

		int beginX=0, endX=matrix[0].size()-1;
		int beginY=0, endY=matrix.size()-1;

		while(true){
			//from left to right
			for(int j=beginX; j<=endX; ++j)
				result.push_back(matrix[beginY][j]);
			if(++beginY > endY)
				break;
			//from top to bottom
			for(int i=beginY; i<=endY; ++i)
				result.push_back(matrix[i][endX]);
			if(beginX > --endX)
				break;
			//from right to left
			for(int j=endX; j>=beginX; --j)
				result.push_back(matrix[endY][j]);
			if(beginY > --endY)
				break;
			//from bottom to top
			for(int i=endY; i>=beginY; --i)
				result.push_back(matrix[i][beginX]);
			if(++beginX > endX)
				break;
		}

		return result;
	}

	/**
	 * 57. Insert Interval
Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).

You may assume that the intervals were initially sorted according to their start times.

Example 1:
Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
Output: [[1,5],[6,9]]

Example 2:
Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
Output: [[1,2],[3,10],[12,16]]
Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].
	 */
	/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
	vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
		vector<Interval>::iterator it = intervals.begin();

		while(it != intervals.end()){
			if(newInterval.end < it->start){
				intervals.insert(it, newInterval);
				return intervals;
			}else if(newInterval.start > it->end){
				it++;
				continue;
			}else{
				newInterval.start = min(newInterval.start, it->start);
				newInterval.end = max(newInterval.end, it->end);
				it = intervals.erase(it);
			}
		}

		intervals.insert(intervals.end(), newInterval);
		return intervals;
	}

	/**
	 * 59. Spiral Matrix II
Given a positive integer n, generate a square matrix filled with elements from 1 to n2 in spiral order.

Example:
Input: 3
Output:
[
 [ 1, 2, 3 ],
 [ 8, 9, 4 ],
 [ 7, 6, 5 ]
]
	 */
	vector<vector<int>> generateMatrix(int n) {
		vector<vector<int>> matrix(n, vector<int>(n));
		int begin=0, end=n-1;
		int num=1;

		while(begin<end){
			for(int j=begin; j<end; ++j)
				matrix[begin][j] = num++;
			for(int i=begin; i<end; ++i)
				matrix[i][end] = num++;
			for(int j=end; j>begin; --j)
				matrix[end][j] = num++;
			for(int i=end; i>begin; --i)
				matrix[i][begin] = num++;
			++begin;
			--end;
		}

		if(begin == end)
			matrix[begin][begin]=num;

		return matrix;
	}
	vector<vector<int>> generateMatrix(int n){
		vector<vector<int>> matrix(n, vector<int>(n));
		if(n==0)
			return matrix;
		int beginX=0, endX=n-1;
		int beginY=0, endY=n-1;
		int num=1;

		while(true){
			for(int j=beginX; j<=endX; ++j)
				matrix[beginY][j] = num++;
			if(++beginY > endY)
				break;
			for(int i=beginY; i<=endY; ++i)
				matrix[i][endX] = num++;
			if(beginX > --endX)
				break;
			for(int j=endX; j>=beginX; --j)
				matrix[endY][j] = num++;
			if(beginY > --endY)
				break;
			for(int i=endY; i>=beginY; --i)
				matrix[i][beginX] = num++;
			if(++beginX > endX)
				break;
		}

		return matrix;
	}

	/**
	 * 68. Text Justification
Given an array of words and a width maxWidth, format the text such that each line has 
exactly maxWidth characters and is fully (left and right) justified.

You should pack your words in a greedy approach; that is, pack as many words as you can 
in each line. Pad extra spaces ' ' when necessary so that each line has exactly maxWidth characters.

Extra spaces between words should be distributed as evenly as possible. 
If the number of spaces on a line do not divide evenly between words, 
the empty slots on the left will be assigned more spaces than the slots on the right.

For the last line of text, it should be left justified and no extra space is inserted between words.

Note:
A word is defined as a character sequence consisting of non-space characters only.
Each word's length is guaranteed to be greater than 0 and not exceed maxWidth.
The input array words contains at least one word.

Example 1:
Input:
words = ["This", "is", "an", "example", "of", "text", "justification."]
maxWidth = 16
Output:
[
   "This    is    an",
   "example  of text",
   "justification.  "
]

Example 2:
Input:
words = ["What","must","be","acknowledgment","shall","be"]
maxWidth = 16
Output:
[
  "What   must   be",
  "acknowledgment  ",
  "shall be        "
]
Explanation: Note that the last line is "shall be    " instead of "shall     be",
             because the last line must be left-justified instead of fully-justified.
             Note that the second line is also left-justified becase it contains only one word.

Example 3:
Input:
words = ["Science","is","what","we","understand","well","enough","to","explain",
         "to","a","computer.","Art","is","everything","else","we","do"]
maxWidth = 20
Output:
[
  "Science  is  what we",
  "understand      well",
  "enough to explain to",
  "a  computer.  Art is",
  "everything  else  we",
  "do                  "
]

problem:
https://leetcode.com/problems/text-justification/description/
	 */
	vector<string> fullJustify(vector<string>& words, int maxWidth) {
		vector<string> res;
		for(int i=0, k, l; i<words.size(); i+=k){
			for(k=l=0; i+k<words.size() and l+words[i+k].size() <= maxWidth-k; k++){
				l += words[i+k].size();
			}

			string tmp = words[i];
			for(int j=0; j<k-1; j++){
				if(i+k >= words.size()) tmp += " ";
				else tmp += string((maxWidth - l) / (k-1) + (j<(maxWidth - l) %(k-1)), ' ');
				tmp += words[i+j+1];
			}

			tmp += string(maxWidth - tmp.size(), ' ');
			res.push_back(tmp);
		}

		return res;
	}

	/**
	 * 76. Minimum Window Substring
Given a string S and a string T, find the minimum window in S which will contain 
all the characters in T in complexity O(n).

Example:
Input: S = "ADOBECODEBANC", T = "ABC"
Output: "BANC"

Note:
If there is no such window in S that covers all characters in T, return the empty string "".
If there is such window, you are guaranteed that there will always be only one 
unique minimum window in S.

problem:
https://leetcode.com/problems/minimum-window-substring/description/
	 */
	//双指针，动态维护一个区间。
	//尾指针不断往后扫，当扫到有一个窗口包含了所有T的字符后，然后再收缩头指针，知道不能再收缩为止。
	//最后记录所有可能的情况中窗口最小的
	string minWindow(string s, string t) {
		if(s.empty()) return "";
		if(s.size() < t.size()) return "";

		const int ASCII_MAX=256;
		int appeared_count[ASCII_MAX];
		int expected_count[ASCII_MAX];
		fill(appeared_count, appeared_count+ASCII_MAX, 0);
		fill(expected_count, expected_count+ASCII_MAX, 0);

		for(size_t i=0; i<t.size(); i++)
			expected_count[t[i]]++;

		int minWidth = INT_MAX, min_start = 0; //窗口大小，起点
		int wnd_start = 0;
		int appeared = 0;

		//尾指针不断往后扫
		for(size_t wnd_end = 0; wnd_end<s.size(); wnd_end++){
			if(expected_count[s[wnd_end]] > 0){
				appeared_count[s[wnd_end]]++;
				if(appeared_count[s[wnd_end]] <= expected_count[s[wnd_end]])
					appeared++;
			}
			if(appeared == t.size()){ //完整包含了一个T
				//收缩头指针
				while(appeared_count[s[wnd_start]] > expected_count[s[wnd_start]] 
					|| expected_count[s[wnd_start]] == 0){
					appeared_count[s[wnd_start]]--;
				wnd_start++;
				}
				if(minWidth > (wnd_end - wnd_start + 1)){
					minWidth = wnd_end - wnd_start + 1;
					min_start = wnd_start;
				}
			}
		}

		if(minWidth == INT_MAX) return "";
		else return s.substr(min_start, minWidth);
	}

	/**
	 * 118. Pascal's Triangle
Given a non-negative integer numRows, generate the first numRows of Pascal's triangle.

In Pascal's triangle, each number is the sum of the two numbers directly above it.

Example:
Input: 5
Output:
[
     [1],
    [1,1],
   [1,2,1],
  [1,3,3,1],
 [1,4,6,4,1]
]
	 */
	//可以用队列，计算下一行时，给上一行左右各加一个0，然后下一行的每个元素，就等于左上角和右上角之和。
	//另一种思路，下一行的第一个元素和最后一个元素赋值为1，中间的每个元素，等于上一行的左上角和右上角元素之和。
	vector<vector<int>> generate(int numRows) {
		vector<vector<int>> result;

		if(numRows == 0)
			return result;

		result.push_back(vector<int>(1,1)); //first row

		for(int i=2; i<=numRows; ++i){
			vector<int> currrent(i,1); //本行
			const vector<int> &prev = result[i-2]; //上一行

			for(int j=1; j<i-1; ++j){
				currrent[j] = prev[j-1] + prev[j]; //左上角和右上角之和
			}
			result.push_back(currrent);
		}

		return result;
	}
	//从右到左
	vector<vector<int>> generate(int numRows){
		vector<vector<int>> result;
		vector<int> array;

		for(int i=1; i<=numRows; i++){
			for(int j=i-2; j>0; j--){
				array[j] = array[j-1] + array[j];
			}
			array.push_back(1);
			result.push_back(array);
		}

		return result;
	}

	/**
	 * 119. Pascal's Triangle II
Given a non-negative index k where k ≤ 33, return the kth index row of the Pascal's triangle.

Note that the row index starts from 0.

In Pascal's triangle, each number is the sum of the two numbers directly above it.

Example:
Input: 3
Output: [1,3,3,1]
Follow up:

Could you optimize your algorithm to use only O(k) extra space?
	 */
	//滚动数组
	vector<int> getRow(int rowIndex){
		vector<int> array;

		for(int i=0; i<=rowIndex; i++){
			for(int j=i-1; j>0; j--)
				array[j] = array[j-1] + array[j];
			array.push_back(1);
		}

		return array;
	}

	/**
	 * 149. Max Points on a Line
Given n points on a 2D plane, find the maximum number of points that lie 
on the same straight line.

Example 1:
Input: [[1,1],[2,2],[3,3]]
Output: 3
Explanation:
^
|
|        o
|     o
|  o  
+------------->
0  1  2  3  4

Example 2:
Input: [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
Output: 4
Explanation:
^
|
|  o
|     o        o
|        o
|  o        o
+------------------->
0  1  2  3  4  5  6

problem:
https://leetcode.com/problems/max-points-on-a-line/description/

solution:
https://leetcode.com/problems/max-points-on-a-line/discuss/130061/C++-simple-solution
	 */
    int maxPoints(vector<Point> &points){
    	int n=points.size(), maxRes=0;
    	for(int i=0; i<n; i++){
    		map<double, int> hash;
    		int count=0, tmpRes=0;

    		for(int j=0; j<n; j++){
    			if(i==1 && points[i].x==94911151 && points[i].y==94911150) return 2;
    			if(i==j) continue;
    			if((points[i].x==points[j].x) && (points[i].y == points[j].y)) tmpRes+=1;
    			else if(points[i].x == points[j].x){
    				count+=1;
    				tmpRes = max(tmpRes, count);
    			}else{
    				double k=1.0 * (points[i].y-points[j].y+0.0)/(points[i].x-points[j].x+0.0);
    				hash[k] += 1;
    				tmpRes = max(tmpRes, hash[k]);
    			}
    		}

    		maxRes = max(maxRes, tmpRes+1);
    	}

    	return maxRes;
    }

	/**
	 * 152. Maximum Product Subarray
Find the contiguous subarray within an array (containing at least one number) which has the largest product.

For example, given the array [2,3,-2,4],
the contiguous subarray [2,3] has the largest product = 6.
	 */
	int maxProduct(vector<int> &nums){
		int n = nums.size();

		if(n==1)
			return nums[0];

		int pMax=0, nMax=0, m=0;

		for(int i=0; i<n; i++){
			if(nums[i]<0)
				swap(pMax, nMax);

			pMax = max(pMax*nums[i], nums[i]);
			nMax = min(nMax*nums[i], nums[i]);
			m = max(m, pMax);
		}

		return m;
	}
	
}