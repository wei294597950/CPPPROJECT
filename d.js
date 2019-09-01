liness = [['1','2.2'],['2.1','2.1.0.2']]
ans = []
for(var i = 0;i < 2; i++){
    lines = liness[i]
    for(var j = 0;j < lines.length; j++){
        lines[j] = lines[j].split('.')
        if(lines[j].length<4){
            for(var k=0;k<4-lines[j].length+1;k++){
                lines[j].push('0')
            }
        }
    }
    var num = 0;
    while(num<4){
        
        if(parseInt(lines[0][num])<parseInt(lines[1][num]))
           {
            ans.push(true)
            break;
           }
         num++;
    }
        if(num == 4){
            ans.push(false)
        }
}
for(var jj = 0;jj<2;jj++){
    console.log(ans[jj])
}