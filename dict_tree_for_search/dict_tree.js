class TrieNode{
    constructor(){
        this.path = 0; //每个字符经过节点的次数
        this.end = 0;   //代表到该节点的字符串有几个
        this.next = new Array(26).fill(null)
    }
}

class Trie{
    constructor(){
        this.root = new TrieNode()
    }

    insert(str){
        if(!str) 
        return;
        let node = this.root
        for(let i=0;i<str.length;i++){
            let index = str[i].charCodeAt()-'a'.charCodeAt()
            if(!node.next[index]){
                node.next[index] = new TrieNode()
            }
            node.path += 1;
            node = node.next[index];
        }
        node.end += 1;
    }
    search(str){
        if(!str)
        return
        let node = this.root
        for(let i=0;i<str.length;i++){
            // 返回字符串第一个字符的 Unicode 编码:
            let index = str[i].charCodeAt() - 'a'.charCodeAt()
            if(!node.next[index]){
                return 0
            }
            node = node.next[index]
        }
        return node.end
    }
    delete(str){
        if(!str)
        return
        let node = this.root
        for(let i=0;i<str.length;i++){
            // 返回字符串第一个字符的 Unicode 编码:
            let index = str[i].charCodeAt() - 'a'.charCodeAt()
            if(--node.next[index].path == 0){
                node.next[index] = null
                return
            }
            node = node.next[index]
        }
        node.end -= 1

    }

} 