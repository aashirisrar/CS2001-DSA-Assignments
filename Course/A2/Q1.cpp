#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

template <class T>
class Stack
{
private:
    struct Node
    {
        T data;
        Node *next;

        Node(const T &value) : data(value), next(NULL) {}
    };

    Node *top;

public:
    Stack() : top(NULL) {}

    ~Stack()
    {
        while (!isEmpty())
        {
            pop();
        }
    }

    void push(const T &value)
    {
        Node *newNode = new Node(value);
        newNode->next = top;
        top = newNode;
    }

    void pop()
    {
        if (isEmpty())
        {
            return;
        }
        Node *temp = top;
        top = top->next;
        delete temp;
    }

    T &Top()
    {
        return top->data;
    }

    bool isEmpty() const
    {
        return top == nullptr;
    }
};

class XMLTag
{
public:
    string name;
    Stack<string> attributes;

    XMLTag(const string &n) : name(n) {}
};

bool isWhitespace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

bool validateXML(const string &filename)
{
    ifstream file(filename);
    if (!file)
    {
        cout << "Error: Unable to open file " << filename << endl;
        return false;
    }

    Stack<XMLTag> tagStack;
    string line;
    int lineNumber = 0;
    vector<string> errorMessages;

    while (getline(file, line))
    {
        lineNumber++;

        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == '<')
            {
                if (i + 1 < line.length())
                {
                    if (line[i + 1] == '?')
                    {
                        // Check for XML Prolog (<? ... ?>)
                        if (tagStack.isEmpty() && i == 0)
                        {
                            int endPos = line.find("?>", i);
                            if (endPos == string::npos)
                            {
                                errorMessages.push_back("Incomplete XML Prolog on line " + to_string(lineNumber));
                                break;
                            }
                            i = endPos + 1;
                        }
                    }
                    else if (line[i + 1] == '!')
                    {
                        // Check for comments (<!-- ... -->)
                        if (i + 3 < line.length() && line.substr(i + 2, 2) == "--")
                        {
                            int endPos = line.find("-->", i);
                            if (endPos == string::npos)
                            {
                                errorMessages.push_back("Unclosed XML Comment on line " + to_string(lineNumber));
                                break;
                            }
                            i = endPos + 2;
                        }
                    }
                    else if (line[i + 1] == '/')
                    {
                        // Closing tag
                        int endPos = line.find('>', i);
                        if (endPos == string::npos)
                        {
                            errorMessages.push_back("Unclosed tag on line " + to_string(lineNumber));
                            break;
                        }
                        string tagName = line.substr(i + 2, endPos - i - 2);

                        if (tagStack.isEmpty())
                        {
                            errorMessages.push_back("Found closing tag without a matching opening tag for '" + tagName + "' on line " + to_string(lineNumber));
                            break;
                        }

                        if (tagStack.Top().name != tagName)
                        {
                            errorMessages.push_back("Mismatched closing tag. Expected '" + tagStack.Top().name + "', but found '" + tagName + "' on line " + to_string(lineNumber));
                            break;
                        }

                        tagStack.pop();
                        i = endPos;
                    }
                    else
                    {
                        // Opening tag
                        int endPos = line.find('>', i);
                        if (endPos == string::npos)
                        {
                            errorMessages.push_back("Unclosed tag on line " + to_string(lineNumber));
                            break;
                        }
                        string tagText = line.substr(i + 1, endPos - i - 1);

                        // Extract tag name and attributes
                        int tagNameEnd = tagText.find_first_of(" /");
                        string tagName = tagText.substr(0, tagNameEnd);
                        tagStack.push(XMLTag(tagName));

                        // Check if there are attributes
                        if (tagNameEnd != string::npos)
                        {
                            int attrStart = tagNameEnd;
                            while (attrStart < tagText.length())
                            {
                                // Skip whitespace
                                while (attrStart < tagText.length() && isWhitespace(tagText[attrStart]))
                                {
                                    attrStart++;
                                }

                                // Find attribute name
                                int attrNameEnd = tagText.find('=', attrStart);
                                if (attrNameEnd == string::npos)
                                {
                                    errorMessages.push_back("Malformed attribute on line " + to_string(lineNumber));
                                    break;
                                }
                                string attributeName = tagText.substr(attrStart, attrNameEnd - attrStart);

                                // Find the attribute value
                                attrStart = attrNameEnd + 1;
                                if (attrStart >= tagText.length())
                                {
                                    errorMessages.push_back("Malformed attribute on line " + to_string(lineNumber));
                                    break;
                                }
                                char quoteChar = tagText[attrStart];
                                int attrValueEnd = tagText.find(quoteChar, attrStart + 1);
                                if (attrValueEnd == string::npos)
                                {
                                    errorMessages.push_back("Unclosed attribute value on line " + to_string(lineNumber));
                                    break;
                                }

                                tagStack.Top().attributes.push(attributeName);
                                attrStart = attrValueEnd + 1;
                            }
                        }
                        i = endPos;
                    }
                }
            }
        }
    }

    while (!tagStack.isEmpty())
    {
        errorMessages.push_back("Unclosed tag '" + tagStack.Top().name + "'");
        tagStack.pop();
    }

    if (!errorMessages.empty())
    {
        cout << "Errors found in the XML file:" << endl;
        for (const string &errorMessage : errorMessages)
        {
            cout << errorMessage << endl;
        }
    }
    else
    {
        cout << "XML is well-formed and valid." << endl;
    }

    return errorMessages.empty();
}

int main()
{
    validateXML("xml.txt");

    return 0;
}
