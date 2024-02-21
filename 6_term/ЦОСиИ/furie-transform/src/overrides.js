import Complex from 'complex.js';

Number.prototype.arrange = function() {
    let arr = [];

    for (let i = 0; i < Number(this); i += 1){
        arr.push(i);
    }

    return arr;
}

Array.prototype.multiplyWithNumber = function(number) {
    return this.map((item) => item * number);
}

Complex.prototype.cexp = function(dst) {
	var er = Math.exp(this.re);
	dst.re = er * Math.cos(this.im);
	dst.im = er * Math.sin(this.im);
	return dst;
}