class Node{
    constructor(data, next = null){
        this.data = data;
        this.next = next;
    }
}
class Stack{
    constructor(){
        this.head = null;
    }
    push(data){
        const node = new Node(data);
        if (!this.head){
            this.head = node;
        } else{
            const temp = this.head;
            this.head = node;
            this.head.next = temp;
        }
    }
    pop(){
        if (!this.head){
            return console.error("Stack is empty");
        }
        this.head = this.head.next;
    }
    peek(){
        if (!this.head){
            return console.error("Stack is empty");
        }
        return this.head;
    }
    count(){
        if (!this.head){
            return console.error("Stack is empty");
        }
        let current = this.head;
        let c = 0;
        while(current){
            c++;
            current = current.next;
        }
        return c;
    }
}
const arr = new Stack();
arr.push(1);
arr.push(1);
arr.push(1);
// arr.push(2);
// console.log(arr.peek());
console.log(arr.count());
// console.log(arr);