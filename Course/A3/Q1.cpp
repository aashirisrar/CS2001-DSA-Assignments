#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;
using namespace sf;

const int circleRadius = 300;

RenderWindow window(VideoMode(850, 850), "Josephus Problem");

template <class T>
class Queue
{
    class Node
    {
    public:
        T data;
        Node *next;

        Node(T data)
        {
            this->data = data;
            next = NULL;
        }
    };

    Node *front;
    Node *rear;
    int size;

public:
    Queue()
    {
        front = NULL;
        rear = NULL;
        size = 0;
    }

    void enqueue(T element)
    {
        Node *newNode = new Node(element);

        if (isEmpty())
        {
            front = newNode;
            rear = newNode;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
        }

        size++;
    }

    T dequeue()
    {
        if (!isEmpty())
        {
            Node *temp = front;
            T tempData = front->data;
            front = front->next;
            size--;
            delete temp;
            return tempData;
        }
        return T();
    }

    int Size()
    {
        return size;
    }

    bool isEmpty()
    {
        return front == NULL;
    }

    T Front()
    {
        if (!isEmpty())
        {
            return front->data;
        }
        return T();
    }

    T Rear()
    {
        if (!isEmpty())
        {
            return rear->data;
        }
        return T();
    }

    ~Queue()
    {
        front = NULL;
        rear = NULL;
    }
};

struct Soldier
{
    Sprite spr;
    bool alive = true;
};

int main()
{
    Texture texSp;
    texSp.loadFromFile("images/amongUs.png");
    Sprite sp(texSp);

    int n, k;

    cout << "Enter the value for N:";
    cin >> n;

    cout << "Enter the value for K:";
    cin >> k;

    Queue<Soldier> soldiers;

    for (int i = 0; i < n; ++i)
    {
        float angle = 2 * 3.14 * i / n - 3.14 / 2.0;
        float x = 400 + circleRadius * std::cos(angle);
        float y = 400 + circleRadius * std::sin(angle);

        Soldier soldier;
        soldier.spr = sp;
        soldier.spr.setPosition(x, y);
        soldiers.enqueue(soldier);
    }

    int eliminatedSoldiers = 0;

    Soldier eliminatedSoldier;
    eliminatedSoldier.spr = sp;
    eliminatedSoldier.spr.setColor(Color::Red);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }

        // displaying the eliminated player and removing it
        if (eliminatedSoldiers < n)
        {
            for (int i = 0; i < k - 1; i++)
            {
                Soldier temp = soldiers.Front();
                soldiers.dequeue();
                soldiers.enqueue(temp);
            }

            Soldier eliminated = soldiers.Front();
            eliminated.alive = false;
            eliminatedSoldiers++;
            eliminatedSoldier.spr.setPosition(eliminated.spr.getPosition());
            soldiers.dequeue();
        }

        window.clear();

        // displaying the remaining soldiers
        Queue<Soldier> survivingSoldiers;
        int remainingSoldiers = soldiers.Size();
        for (int i = 0; i < remainingSoldiers; i++)
        {
            Soldier soldier = soldiers.Front();
            soldiers.dequeue();
            if (soldier.alive)
            {
                survivingSoldiers.enqueue(soldier);
                window.draw(soldier.spr);
            }
        }
        soldiers = survivingSoldiers;

        if (eliminatedSoldiers > 0)
        {
            window.draw(eliminatedSoldier.spr);
            sleep(seconds(2));
        }

        // Displaying text
        Font font;
        if (!font.loadFromFile("fonts/gomarice_no_continue.ttf"))
        {
            return 1;
        }

        Text text("Josephus Problem", font, 30);
        text.setPosition(325, 25);
        text.setFillColor(Color::White);
        window.draw(text);

        Text displayN("N: " + to_string(n), font, 35);
        displayN.setPosition(415, 425);
        displayN.setFillColor(Color::White);
        window.draw(displayN);

        Text displayK("K: " + to_string(k), font, 35);
        displayK.setPosition(420, 465);
        displayK.setFillColor(Color::White);
        window.draw(displayK);

        window.display();

        // for displaying the winner
        if (eliminatedSoldiers == n - 1)
        {
            for (int i = 0; i < n; i++)
            {
                if (soldiers.Front().alive)
                {
                    window.clear();
                    window.draw(soldiers.Front().spr);
                    window.display();
                    sleep(seconds(3));
                    window.close();
                    break;
                }
                soldiers.enqueue(soldiers.Front());
                soldiers.dequeue();
            }
        }
    }

    return 0;
}
