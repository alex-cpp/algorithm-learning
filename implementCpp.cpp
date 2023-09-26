/**
 * @file  [implementCpp.cpp]
 * @brief [implement CPP] in C++
 * @details
 *      CPP class implement
 *      1. Song
 *
 */

#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <set>

/*
* Implement the unique_names method. When passed two vectors of names, 
* it will return a vector containing the names that appear in either or both vectors.
* The returned vector should have no duplicates.
*/
std::vector<std::string> unique_names(const std::vector<std::string>& names1, const std::vector<std::string>& names2)
{
    //throw std::logic_error("Waiting to be implemented");
    std::set <std::string> tmpSet;
    for (auto element : names1)
    {
        tmpSet.insert(element);
    }
    for (auto element2 : names2)
    {
        tmpSet.insert(element2);
    }

    std::vector<std::string> uniName;

    for (auto setEle : tmpSet)
    {
        uniName.push_back(setEle);
    }
    return uniName;
}


/*
* A palindrome is a word that reads the same backward or forward.
Write a function that checks if a given word is a palindrome. Character case should be ignored.
*/
bool isPalindrome(const std::string& word)
{
    //throw std::logic_error("Waiting to be implemented");
    int len = word.length();
    for (int i = 0; i < len / 2; i++)
    {
        if (tolower(word[i]) != tolower(word[len - 1 - i])) return false;
    }

    return true;
}

/*
* Binary search tree (BST) is a binary tree where the value of each node is larger or equal to the values in all the nodes in that node's left subtree and is smaller than the values in all the nodes in that node's right subtree.
Write a function that, efficiently with respect to time used, checks if a given binary search tree contains a given value.
*/
class Node
{
public:
    Node(int value, Node* left, Node* right)
    {
        this->value = value;
        this->left = left;
        this->right = right;
    }

    int getValue() const
    {
        return value;
    }

    Node* getLeft() const
    {
        return left;
    }

    Node* getRight() const
    {
        return right;
    }

private:
    int value;
    Node* left;
    Node* right;
};

class BinarySearchTree
{
public:
    static bool contains(const Node& root, int value)
    {
        //throw std::logic_error("Waiting to be implemented");
        //if (root == NULL) return false;
        if (root.getValue() == value) return true;
        if (root.getValue() > value)
        {
            if (root.getLeft() == NULL) return false;
            return contains(*(root.getLeft()), value);
        }

        if (root.getValue() < value)
        {
            if (root.getRight() == NULL) return false;
            return contains(*(root.getRight()), value);
        }

        return false;

    }
};

/**
*A playlist is considered a repeating playlist if any of the songs contain a pointer to a previous song in the playlist. 
*Otherwise, the playlist will end with the last song which points to NULL.
*Implement a function isRepeatingPlaylist that, efficiently with respect to time used, 
*returns true if a playlist is repeating or false if it is not.
*/
class Song
{
public:
    Song(std::string name) : name(name), nextSong(NULL) {}

    void next(Song* song)
    {
        this->nextSong = song;
    }

    bool isRepeatingPlaylist()
    {
        //throw std::logic_error("Waiting to be implemented");
        if (this->nextSong == NULL) return false;
        Song* nextp, * next_nextp;
        nextp = this->nextSong;
        next_nextp = nextp->nextSong;
        while (nextp != NULL && next_nextp != NULL)
        {
            if (nextp == next_nextp) return true;
            nextp = nextp->nextSong;
            next_nextp = next_nextp->nextSong;
            if (next_nextp == NULL) return false;
            next_nextp = next_nextp->nextSong;
        }
        return false;
    }

private:
    const std::string name;
    Song* nextSong;
};

/*
* User interface contains two types of user input controls: TextInput, which accepts all characters and NumericInput, which accepts only digits.
*Implement the following methods:
**add on class TextInput - adds the given character to the current value
**getValue on class TextInput - returns the current value
**add on class NumericInput - overrides the base class method so that each non-numeric character is ignored
*/

class TextInput
{
public:
    virtual void add(char c)
    {
        this->text += c;
    }

    std::string getValue() { return text; }

private:
    std::string text;
};


class NumericInput : public TextInput {
public:
    virtual void add(char c)
    {
        if (c >= '0' && c <= '9')
        {
            TextInput::add(c);
        }
        /*else
        {
            return;
        }*/
    }
};

//#ifndef RunTests
void implementCppTest()
{

    // unique_names()
    std::vector<std::string> names1 = { "Ava", "Emma", "Olivia" };
    std::vector<std::string> names2 = { "Olivia", "Sophia", "Emma" };

    std::vector<std::string> result = unique_names(names1, names2);
    std::cout << "The merged name list is : ";
    for (auto element : result)
    {
        std::cout << element << ' '; // should print Ava Emma Olivia Sophia
    }
    std::cout << std::endl << std::endl;

    //isPalindrome
    std::string txt1 = "Deleveled";
    std::cout << txt1 << " is palindrom? -- " << std::boolalpha << isPalindrome(txt1);
    std::cout << std::endl;
    std::string txt2 = "Deleveked";
    std::cout << txt2 << " is palindrom? -- " << std::boolalpha << isPalindrome(txt2);
    std::cout << std::endl << std::endl;

    //Binary search tree (BST)
    Node n1(1, NULL, NULL);
    Node n3(3, NULL, NULL);
    Node n2(2, &n1, &n3);

    std::cout << "3 is in BST? -- " << std::boolalpha << BinarySearchTree::contains(n2, 3);  //contains is static, don't need to new a class
    std::cout << std::endl;
    std::cout << "4 is in BST? -- " << std::boolalpha << BinarySearchTree::contains(n2, 4);
    std::cout << std::endl << std::endl;

    // class Song
    Song* first = new Song("Hello");
    Song* second = new Song("Eye of the tiger");
    Song* third = new Song("good good study");
    Song* forth = new Song("day day up");

    first->next(second);
    second->next(third);
    third->next(forth);

    std::cout << "playlist 1 is report? true or false? -- " ;
    std::cout << std::boolalpha << first->isRepeatingPlaylist(); //
    std::cout << std::endl;

    forth->next(first);

    std::cout << "playlist 2 is report? true or false? -- ";
    std::cout << std::boolalpha << first->isRepeatingPlaylist();
    std::cout << std::endl << std::endl;

    //class NumericInput : public TextInput
    TextInput* input = new NumericInput();
    input->add('1');
    input->add('a');
    input->add('0');
    std::cout << "NumericInput:" << input->getValue();  // 10,  non-numeric character is ignored
    std::cout << std::endl << std::endl;
}
//#endif

