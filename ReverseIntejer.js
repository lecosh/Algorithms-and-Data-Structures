let x = 123
// let s = String(x)
// let a =  s.split('').reverse().join('');
// let x1 = Number(a)
var reverse = function(x) {
    let s = String(x);
    if(s.includes('-')){
        s = Number(s.substring(1).split('').reverse().join(''));
        if (s > 2147483647) return 0;
        s = '-' + s;
    }
    else {
        s = Number(s.split('').reverse().join(''))
        if (s > 2147483647) return 0;
    }
    return s;
}
reverse(x)
