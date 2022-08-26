class Node{
    constructor(data, index = null, left_child = null, right_child = null){
        this.data = data;
        this.index = index;
        this.left_child = left_child;
        this.right_child = right_child;
    }
}
class BinaryTree{
    constructor() {
        this.root = null;
        this.total_length = -1;
    }

    push(data){
        const node = new Node(data);
        if (!this.root){
            this.root = node;
            this.total_length++;
            node.index = this.total_length;
            return ;
        }
        let current = this.root;
        const size = this.total_length + 1;
        while(size !== this.total_length){
            if (data > current.data && !current.right_child){
                current.right_child = node;
                this.total_length++;
                node.index = this.total_length;
            }
            if (data < current.data && !current.left_child){
                current.left_child = node;
                this.total_length++;
                node.index = this.total_length;
            }
            if (data > current.data && current.right_child){
                current = current.right_child;
            }
            if (data < current.data && current.left_child){
                current = current.left_child;
            }
        }
        
        
    }
    find(data){
        if (!this.root){
            return console.log('The tree is empty');
        }
        let current = this.root;;
        while(true){
            if (current.data === data){
                return console.log(current.index);
            }
            if (data > current.data && current.right_child){
                current = current.right_child;
            } else if(data > current.data && !current.right_child){
                return console.error("Can't find element");
            }
            if (data < current.data && current.left_child){
                current = current.left_child;
            } else if (data < current.data && !current.left_child){
                return console.error("Can't find element");
            }
        }
    }
    min(){
        if (!this.root){
            return console.log('The tree is empty');
        }
        let current = this.root;
        while(current.left_child){
            current = current.left_child;
        }
        return console.log('Element:', current.data, ',', 'Index:', current.index);
    }
    max(){
        if (!this.root){
            return console.log('The tree is empty');
        }
        let current = this.root;
        while(current.right_child){
            current = current.right_child;
        }
        return console.log('Element:', current.data, ',', 'Index:', current.index);
    }
}
const tree = new BinaryTree();
tree.push(50);
tree.push(46);
tree.push(60);
tree.push(1);
tree.push(55);
tree.push(65);
tree.max();
// console.log(tree);