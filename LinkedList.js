class Node{
    constructor(data, next = null){
        this.data = data;
        this.next = next;
    }
}
class LinkedList{
    constructor(){
        this.head = null;
        this.tail = null;
    }
    append(data){
        const node = new Node(data)

        if (this.tail){
            this.tail.next = node;
        }
        if (!this.head){
            this.head = node;
        }

        this.tail = node;
    }
    prepend(data){
        const node = new Node(data, this.head);

        if (!this.tail){
            this.tail = node;
        }
        this.head = node;
    }
    find(data){
        let current = this.head;
        while(current){
            if (current.data == data){
                return true;
            }
            current = current.next;
        }
    }
    toArray(){
        let current = this.head;
        let arr = [];
        while(current){
            arr.push(current.data)
            current = current.next;
        }
        return arr;
    }
    delete(data){
        if (!this.head){
            return console.error("List is empty");
        }
        let current = this.head;
        while(current.next){
            if (current.next.data === data){
                current.next = current.next.next;
            } else{
                current = current.next
            }
        }
        if (this.head.data === data){
            this.head = this.head.next;
        }
    }
}
const list = new LinkedList();
// list.append(1)
// list.append(2)
// list.append(3)
// list.append(1)
// list.append(2)
// list.append(1)
list.delete(1)
console.log(list.toArray());