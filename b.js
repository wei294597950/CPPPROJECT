var ans = [['a1','a2',],['b1','b2',],['c1','c2'],['d1','d2']]
readlines().length

var result = []
var resultstr = ''
var j = 0
while(j<ans.length-1){

    resultstr = ''  
    var temp = ''
    for(var k=0;k<ans[j].length;k++){
        var str = ''
        for(var l=0;l<ans[j+1].length;l++){
            str = ans[j][k]+' '+ans[j+1][l]+','
            temp += str
        }  
    }
    resultstr+=temp
    result = resultstr.substr(0,resultstr.length-1).split(",")
    ans.shift(0);
    ans.shift(1);
    ans.unshift(result)
    
}
console.log(resultstr.substr(0,resultstr.length-1))