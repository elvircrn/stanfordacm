#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <cstring>
#include <functional>

struct node {
	std::vector<node *> nodes;
	bool isWord{};
	size_t id{};
	size_t childrenSize;

	node(size_t _childrenSize) : childrenSize(_childrenSize) {
		nodes.resize(childrenSize);
	}

	node *initOrNext(size_t next) {
		if (nodes[next] == nullptr) {
			nodes[next] = new node(childrenSize);
		}
		return nodes[next];
	}

	node *getNext(size_t next) {
		return nodes[next];
	}
};

struct trie {
	std::function<size_t(char)> toId;
	node *root = nullptr;
	size_t childrenCount;

	trie(size_t _childrenCount) : childrenCount(_childrenCount) {
		toId = [](char c) -> int { return c - 'a'; };
	}

	trie(size_t _childrenCount, const std::function<size_t(char c)> &f) : childrenCount(_childrenCount) {
		toId = f;
	}

	node* addWord(const std::string &str) {
		if (root == nullptr) {
			root = new node(childrenCount);
		}

		node *node = root;
		for (const auto &c: str) {
			size_t next = toId(c);
			node = node->initOrNext(next);
		}

		node->isWord = true;

		return node;
	}

	node* addWord(const std::string &str, size_t id) {
		auto node = addWord(str);
		node->id = id;
		return node;
	}

	node* getWord(const std::string &str) {
		auto node = root;
		for (const auto &c: str) {
			size_t nextId = toId(c);
			node = node->getNext(nextId);
			if (node == nullptr) {
				return nullptr;
			}
		}
		return node;
	}
};

int main() {
	trie t(26);
	auto testWord = "asdasdasd";
	t.addWord(testWord, 10);
	std::cout << t.getWord(testWord)->id << '\n';
	std::cout << t.getWord(testWord)->isWord << '\n';
	return 0;
}

