#include <bits/stdc++.h>

using namespace std;

class Node {
 public:
  Node(const string& name) : _name(name) {}

  Node* get_or_create_child(const string& name) {
    // If the child already exists, return it.
    for (int i = 0; i < (int) _children.size(); i++) {
      if (_children[i]->_name == name) {
        return _children[i];
      }
    }

    // Otherwise, create and return it.
    Node* child = new Node(name);
    _children.push_back(child);
    return child;
  }

  string _name;
  vector<Node*> _children;
};

struct cmp {
  bool operator ()(Node* n1, Node* n2) {
    return n1->_name < n2->_name;
  }
};

void dfs(Node* node, const int depth) {
  if (!node) {
    return;
  }

  for (int i = 0; i < depth; i++) {
    cout << " ";
  }
  if (!node->_name.empty()) {
    cout << node->_name << endl;
  }

  sort(node->_children.begin(),
       node->_children.end(),
       cmp());

  for (int i = 0; i < (int) node->_children.size(); i++) {
    dfs(node->_children[i], depth + 1);
  }
}


int main() {
  int N;
  cin >> N;

  Node* root_node = new Node("");

  for (int i = 0; i < N; i++) {
    string filename;
    cin >> filename;

    Node* current = root_node;
    size_t begin = 0;

    while (begin != filename.npos) {
      size_t next = filename.find('\\', begin);
      string component_name = filename.substr(begin, next - begin);

      current = current->get_or_create_child(component_name);

      if (next == filename.npos) {
        break;
      }
      begin = next + 1;
    }
  }

  // Filesystem tree preorder DFS
  dfs(root_node, -1);
}
