/*
    设计一个使用单词列表进行初始化的数据结构，单词列表中的单词 互不相同 。 如果给出一个单词，请判定能否只将这个单词中一个字母换成另一个字母，使得所形成的新单词存在于你构建的字典中。

    实现 MagicDictionary 类：

    MagicDictionary() 初始化对象
    void buildDict(String[] dictionary) 使用字符串数组 dictionary 设定该数据结构，dictionary 中的字符串互不相同
    bool search(String searchWord) 给定一个字符串 searchWord ，判定能否只将字符串中 一个 字母换成另一个字母，使得所形成的新字符串能够与字典中的任一字符串匹配。如果可以，返回 true ；否则，返回 false 。


    提示：

    1 <= dictionary.length <= 100
    1 <= dictionary[i].length <= 100
    dictionary[i] 仅由小写英文字母组成
    dictionary 中的所有字符串 互不相同
    1 <= searchWord.length <= 100
    searchWord 仅由小写英文字母组成
    buildDict 仅在 search 之前调用一次
    最多调用 100 次 search

    来源：力扣（LeetCode）
    链接：https://leetcode.cn/problems/implement-magic-dictionary
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

class MagicDictionary {
public:
    // C++
    // 执行用时： 32 ms, 在所有 C++ 提交中击败了87.04%的用户
    // 内存消耗：17.4 MB, 在所有 C++ 提交中击败了94.44%的用户
    vector<string> dic;
    MagicDictionary() {

    }
    
    void buildDict(vector<string> dictionary) {
        dic = dictionary;
    }
    
    bool search(string searchWord) {
        for(int i=0;i<dic.size();i++)// 遍历所有字符串
        {
            if(dic[i].length() == searchWord.length()){ // 长度要一样
                int difference=0;
                for(int j=0;j<searchWord.length();j++){ // 遍历每个字符
                    if(difference<=1){ // 差异小于等于一个字符
                        if(dic[i][j] != searchWord[j]){ // 字符是否不一样
                            difference++; // 差异加加
                        }
                    }else{ // 差异大于了1个
                        break; // 跳出循环
                    }
                }
                if(difference == 1){ // 如果差异是1个
                    return true; // 返回 true
                }
            }
        }
        return false; // 返回 false
    }
};

/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary* obj = new MagicDictionary();
 * obj->buildDict(dictionary);
 * bool param_2 = obj->search(searchWord);
 */