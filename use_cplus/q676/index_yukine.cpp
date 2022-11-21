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