#include <iostream>

using namespace std;

template <class T> class Node {
	private:
		T key;
		Node<T> *left, *right, *parent;
		int color;
		int leaf;

	public:
		Node<T>(T key) {
			this->key = key;
			left = right = parent = NULL;
			leaf = 1;
		}

		T getKey() {return key;}
		int getColor() {return color;}
		int isLeaf() {return leaf;}
		Node<T>* getLeft() {return left;}
		Node<T>* getRight() {return right;}
		Node<T>* getParent() {return parent;}
		void setKey(T key) {this->key = key;}
		void setColor(int color) {this->color = color;}
		void setLeaf(int leaf) {this->leaf = leaf;}
		void setLeft(Node<T>* left) {this->left = left;}
		void setRight(Node<T>* right) {this->right = right;}
		void setParent(Node<T>* parent) {this->parent = parent;}
};

  template <class H> class RBTree{

    private:
      Node<H>* root;
      int size;
			static const int BLACK = 0;
			static const int RED = 1;
			static const int BLACKBLACK = 2;

		void _preorder(Node<H>* x) {
			if(!x) return;
				cout << x->getKey() << " ";
				_preorder(x->getLeft());
				_preorder(x->getRight());
		}

    void _inorder(Node<H>* x){
      if(!x) return;
      _inorder(x->getLeft());
      cout << x->getKey() << " ";
      _inorder(x->getRight());
    }

		void _postorder(Node<H>* x) {
			if(!x) return;
				_postorder(x->getLeft());
				_postorder(x->getRight());
				cout << x->getKey() << " ";
		}

		Node<H>* search(H x){
			Node<H>* tmp = root;

			while(tmp && tmp->getKey()!=x){
				if (x>tmp->getKey())
					tmp = tmp->getRight();
				else
					tmp = tmp->getLeft();
			}

				return tmp;
		}


    RBTree<H>* rightRotate(Node<H>* y){
      Node<H>* left = y->getLeft();
      Node<H>* parent = y->getParent();
      y->setLeft(left->getRight());
      left->setRight(y);
      if (parent!=NULL){
        if(parent->getLeft()==y) parent->setLeft(left);
        else parent->setRight(left);
      }
      else root = left;
      left->setParent(parent);
      y->setParent(left);
      if (y->getLeft()) y->getLeft()->setParent(y);
      return this;
  }



    RBTree<H>* leftRotate(Node<H>* y){
    	Node<H>* right = y->getRight();
      Node<H>* parent = y->getParent();
      y->setRight(right->getLeft());
      right->setLeft(y);
      if (parent!=NULL){
        if(parent->getLeft()==y) parent->setLeft(right);
        else parent->setRight(right);
      }
      else root = right;
      right->setParent(parent);
      y->setParent(right);
      if (y->getRight()) y->getRight()->setParent(y);
      return this;
  }

	void RBInsertFixup(Node<H> *z) {
		if(z->getParent()!=NULL && z->getParent()->getColor()==BLACK) return;
		if(z == root) {
			z->setColor(BLACK);
			return;
		}
		Node<H> *padre = z->getParent();
		Node<H> *nonno = padre->getParent();
		Node<H> *zio = nonno->getRight();
		if(padre == nonno->getRight()) zio = nonno->getLeft();
		if(zio!=NULL && zio->getColor() == RED) {
			// caso 1
			zio->setColor(BLACK);
			padre->setColor(BLACK);
			nonno->setColor(RED);
			RBInsertFixup(nonno);
			return;
		}
		if(padre == nonno->getLeft()) {
			if(z == padre->getRight()) {
				// caso 3
				this->leftRotate(padre);
				padre = z;
				z = padre->getLeft();
			}
			// caso 2
			this->rightRotate(nonno);
			padre->setColor(BLACK);
			nonno->setColor(RED);
			return;
		}
		else { // casi simmetrici ai precedenti
			if(z == padre->getLeft()) {
				// caso 3
				this->rightRotate(padre);
				padre = z;
				z = padre->getRight();
			}
			// caso 2
			padre->setColor(BLACK);
			nonno->setColor(RED);
			this->leftRotate(nonno);
			return;
		}
	}

    public:

      RBTree<H> *insert(H key) {
  			Node<H>* tmp = root;
  			Node<H>* parent = NULL;
  			while(tmp!=NULL) {
  				parent = tmp;
  				if(key>tmp->getKey()) {
  					tmp = tmp->getRight();
  				}
  				else tmp = tmp->getLeft();
  			}
  			Node<H> *n = new Node<H>(key);
  			if(parent==NULL) root = n;
  			else {
  				n->setParent(parent);
  				if(key>parent->getKey()) {
  					parent->setRight(n);
  				}
  				else parent->setLeft(n);
  				parent->setLeaf(0);
  			}
  			size++;
				n->setColor(RED);
				RBInsertFixup(n);
  			return this;
  		}



      void inorder(){
        _inorder(root);
        cout << endl;
      }

      void preorder(){
        preorder_visit(root);
        cout << endl;
      }

			void postorder(){
        _postorder(root);
        cout << endl;
      }

			RBTree<H> *rightRotate(H key) {
				Node<H> *n = search(key);
				if(n!=NULL) rightRotate(n);
				return this;
			}

			RBTree<H> *leftRotate(H key) {
				Node<H> *n = search(key);
				if(n!=NULL) leftRotate(n);
				return this;
			}



};



  int main(){

    RBTree<int>* rb = new RBTree<int>();
    rb->insert(25)->insert(52)->insert(67)->insert(34)->insert(54)->insert(64)->insert(70)->insert(45);
    rb->postorder();

  }
