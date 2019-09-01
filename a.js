var n = parseInt(readline());
var ans = [];
for(var i = 0;i < n; i++){
    lines = readline().split(" ")
    ans.push(lines)
}
var result = ans
var resultstr = ''
for(var j=0;j<ans.lenth-1;j++){
    var temp = []
    for(var k=0;k<ans[j].length;k++){
        var str = ''
        for(var l=0;l<ans[j+1].length;l++){
            str = ans[j][k]+','+ans[j+1][l]+','
        }
        temp += str
        resultstr+=temp
    }
    result.push[temp]
    ans.splice(0,1);
    ans.unshift(result)  
}
print(resultstr)