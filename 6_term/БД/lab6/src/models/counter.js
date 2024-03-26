class Counter {
    count;

    constructor() {
        this.count = 0;
    }

    increment() {
        this.count++;
    }
    decrement() {
        this.count--;
    }
}

module.exports = { Counter }