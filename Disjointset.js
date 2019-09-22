class Disjointset{
    constructor(count){
        this.parent = new Array(count)
        this.rank = new Array(count)
        for(let i=0;i<count;i++){
            this.parent[i] = i
            this.rank[i] = 1
        }
    }
    find(p){
        while(p != this.parent[p]){
            this.parent[p] = this.parent[this.parent[p]]
            p = this.parent[p]
        }
        return p
    }
    isConnected(p,q){
        return this.find(p) === this.find(q)
    }
    union(p,q){
        let i = this.find(p)
        let j = this.find(q)
        if( i === j)
        return 
        if(this.rank[i] < this.rank[j]){
            this.parent[i] = j
        }else if(this.rank[i] > this.rank[j]){
            this.parent[j] = i
        } else {
            this.parent[i] = j
            this.rank[j] += 1
        }
    }
}