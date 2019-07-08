
#include <vector>
#include <algorithm>
#include <iostream>

class Node;

class Edge
{
public:
    Edge()
    {}

    Edge(Node* from, Node* to, int capacity):
        from(from),
        to(to),
        capacity(capacity)
    {

    }

    Node* from = nullptr;
    Node* to = nullptr;
    int capacity = 0;
    int flow = 0;
};

class Node
{
public:
    Node()
    {}

    Node(bool source, bool sink):
        _source(source),
        _sink(sink)
    {}

    static void edgeFromTo(Node* a, Node* b, int capacity)
    {
        Edge* new_edge = new Edge(a, b, capacity);

        a->neighboursF.push_back(new_edge);
        b->neighboursT.push_back(new_edge);
    }


    bool _source = false;
    bool _sink = false;
    int was = 0;

    std::vector<Edge*> neighboursF;
    std::vector<Edge*> neighboursT;

    virtual ~Node()
    {
        for(Edge* el: neighboursF)
            delete el;
    }
};

class Product: public Node
{
public:
    int x, y;

    Product(int x, int y):
            Node(false, false),
            x(x),
            y(y)
    {}

    static bool isNeighb(Product& a, Product& b)
    {
        return (abs(a.x - b.x) <= 1 && abs(a.y - b.y) <= 1 && (a.x - b.x) * (a.y - b.y) == 0);
    }

    ~Product() override
    {}

};

bool specDFS(std::vector<int>& values, Node* cNode, int* minValue, int key)
{
    if(cNode->was == key)
        return false;

    cNode->was = key;

    if (cNode->_sink)
    {
        *minValue = *(std::min_element(values.begin(), values.end()));
        return true;
    } else
    {
        for (Edge* el: cNode->neighboursF)
        {
            if (el->capacity - el->flow > 0)
            {
                values.push_back(el->capacity - el->flow);
                if (specDFS(values, el->to, minValue, key))
                {
                    el->flow += *minValue;
                    return true;
                }
                else
                {
                    values.pop_back();
                }
            }
        }

        for (Edge* el: cNode->neighboursT)
        {
            if (el->flow > 0)
            {
                values.push_back(el->flow);
                if (specDFS(values, el->from, minValue, key))
                {
                    el->flow -= *minValue;
                    return true;
                }
                else
                {
                    values.pop_back();
                }
            }
        }

        return false;
    }
}

int FFalg(Node* source)
{
    int minValue = 0;
    int result = 0;
    std::vector<int> values;

    int key = 1;

    while(specDFS(values, source, &minValue, key))
    {
        result += minValue;
        minValue = 0;
        values.clear();
        key++;

    }

    return result;

}

int main()
{
    std::cout << "pls insert num of damaged goods\n";
    int num; //num of damaged products;

    std::cin >> num;

    std::cout << "pls insert cost of 1x2 and after 1x1\n";
    int A, B; // costs of 1x2 prod and 1x1 correspondingly

    std::cin >> A >> B;

    if(B * 2 > A)
    {
        std::vector<Product*> dark;
        std::vector<Product*> white;

        for(int i = 0; i < num; i++)
        {

            std::cout << "pls insert coordinates of " << i + 1 << " damaged product\n";
            int x, y;
            std::cin >> x >> y;

            Product* newProd = new Product(x, y);

            if((x + y) % 2 == 0)
            {
                dark.push_back(newProd);

                for(Product* el: white)
                {
                    if(Product::isNeighb(*newProd, *el));
                    {
                        Node::edgeFromTo(newProd, el, 1);
                    }
                }
            }
            else
            {
                white.push_back(newProd);

                for(Product* el: dark)
                {
                    if(Product::isNeighb(*newProd, *el));
                    {
                        Node::edgeFromTo(el, newProd, 1);
                    }
                }
            }
        }

        Node source (true, false);
        Node sink (false, true);

        for(Product* el: dark)
        {
            Node::edgeFromTo(&source, el, 1);
        }

        for(Product* el: white)
        {
            Node::edgeFromTo(el, &sink, 1);
        }

        int flow = FFalg(&source); // num of max pairs(max goods 2x1)

        std::cout << "to replace you need " << A * flow + B * (num - 2 * flow) << " c.u.";
    }
    else
    {
        std::cout << "to replace you need " << B * num << " c.u.";
    }
}


