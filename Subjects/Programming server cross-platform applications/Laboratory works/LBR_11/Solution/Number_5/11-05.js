const rpcws=require('rpc-websockets').Server

let server=new rpcws({port: 4000, host: 'localhost'});

server.setAuth((l)=>{return (l.login == 'Max' && l.password== 'Max1111')});

server.register('square', function (params) {
    return params.length==1? Math.PI*params[0]**2: params[0]*params[1];
}).public();

server.register('sum', function (params) {
    let sum=0;
    params.forEach(element => {
        sum+=element;
    });
    return sum;
}).public();

server.register('mul', function (params) {
    let mul=1;
    params.forEach(element => {
        mul*=element;
    });
    return mul;
}).public();

server.register('fib', function (params) {
    return fib(params);
}).protected();

server.register('fact', function (params) {
    return fact(params);
}).protected();

let fib=n=>{
    if (n <= 1) {
        return 1;
    }
    return fib(n - 1) + fib(n - 2);
};

let fact=n=>{
    return (n == 1 || n == 0) ? 1 : n * fact(n - 1);
};