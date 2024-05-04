#include <bits/stdc++.h>
using namespace std;
char start;

map<char, vector<vector<char>>> readGrammar(const string &filename)
{
    ifstream fin(filename);
    int i, j;
    map<char, vector<vector<char>>> grammar;
    string line;

    bool flag = 0;
    cout << "Grammar: " << '\n';
    while (getline(fin, line))
    {
        if (flag == 0)
        {
            start = line[0], flag = 1;
        }
        cout << line << '\n';
        char nonTerminal = line[0];
        vector<char> production;
        for (int i = 3; i < line.size(); i++)
        {
            if (line[i] == '|')
            {
                grammar[nonTerminal].push_back(production);
                production.clear();
            }
            else
            {
                production.push_back(line[i]);
            }
        }
        grammar[nonTerminal].push_back(production);
    }
    return grammar;
}

void printGrammar(const std::map<char, std::vector<std::vector<char>>> &grammar)
{
    cout << "\nConverted Grammar:" << endl;
    for (const auto &entry : grammar)
    {
        char nonTerminal = entry.first;
        std::string output = "";
        output += nonTerminal;
        output += " -> ";

        bool first = true;

        for (const auto &production : entry.second)
        {
            if (!first)
            {
                output += " | ";
            }
            else
            {
                first = false;
            }

            for (const auto &symbol : production)
            {
                output += symbol;
            }
        }

        std::cout << output << std::endl;
    }
}

void eliminateLeftRecursion(map<char, vector<vector<char>>> &grammar)
{

    map<char, vector<vector<char>>> additionalRules;

    vector<int> usedNonTerminals(26, 0);
    int flag = 0;

    for (auto &entry : grammar)
    {
        char nonTerminal = entry.first;
        vector<vector<char>> nonLeftRecursiveProductions;
        vector<vector<char>> leftRecursiveProductions;

        for (auto &production : entry.second)
        {
            if (production[0] == nonTerminal)
            {

                vector<char> adjustedProduction(production.begin() + 1, production.end());
                leftRecursiveProductions.push_back(adjustedProduction);
            }
            else
            {
                nonLeftRecursiveProductions.push_back(production);
            }
        }

        if (!leftRecursiveProductions.empty())
        {
            flag = 1;
            cout << "Given CFG is not suitable for LL(1) parsing as is has Left Recurssion." << endl;

            char newNonTerminal = 'A';
            while (grammar.count(newNonTerminal) || usedNonTerminals[newNonTerminal - 'A'])
            {
                newNonTerminal++;
            }
            usedNonTerminals[newNonTerminal - 'A'] = 1;

            for (auto &production : nonLeftRecursiveProductions)
            {
                production.push_back(newNonTerminal);
            }

            for (auto &production : leftRecursiveProductions)
            {
                production.push_back(newNonTerminal);
            }
            leftRecursiveProductions.push_back({'#'});

            grammar[nonTerminal] = nonLeftRecursiveProductions;

            additionalRules[newNonTerminal] = leftRecursiveProductions;
        }
    }
    for (auto &entry : additionalRules)
    {
        grammar[entry.first] = entry.second;
    }

    if (flag)
    {
        printGrammar(grammar);
    }
}

set<char> getFirstSet(char nonTerminal, const map<char, vector<vector<char>>> &grammar, map<char, set<char>> &firstSets)
{

    if (firstSets.count(nonTerminal))
    {
        return firstSets[nonTerminal];
    }

    set<char> firstSet;
    bool canDeriveEpsilon = false;

    for (const auto &production : grammar.at(nonTerminal))
    {
        bool canProduceEpsilon = true;

        for (const char &symbol : production)
        {
            if (symbol >= 'A' && symbol <= 'Z')
            {

                set<char> subFirstSet = getFirstSet(symbol, grammar, firstSets);
                firstSet.insert(subFirstSet.begin(), subFirstSet.end());
                firstSet.erase('#');

                if (!subFirstSet.count('#'))
                {
                    canProduceEpsilon = false;
                    break;
                }
            }
            else if (symbol == '#')
            {

                firstSet.insert(symbol);
                break;
            }
            else
            {

                firstSet.insert(symbol);
                canProduceEpsilon = false;
                break;
            }
        }

        if (canProduceEpsilon)
        {
            canDeriveEpsilon = true;
        }
    }

    if (canDeriveEpsilon)
    {
        firstSet.insert('#');
    }

    firstSets[nonTerminal] = firstSet;
    return firstSet;
}

map<char, set<char>> calculateFollowSets(const map<char, vector<vector<char>>> &grammar, char startSymbol, map<char, set<char>> &firstSets)
{
    int i;
    map<char, set<char>> followSets;
    followSets[startSymbol].insert('$');

    int iterations = 10;
    while (iterations--)
    {
        for (auto q : grammar)
        {
            for (auto r : q.second)
            {
                for (i = 0; i < r.size() - 1; i++)
                {
                    if (r[i] >= 'A' && r[i] <= 'Z')
                    {
                        if (!(r[i + 1] >= 'A' && r[i + 1] <= 'Z'))
                            followSets[r[i]].insert(r[i + 1]);
                        else
                        {
                            char temp = r[i + 1];
                            int j = i + 1;
                            while (temp >= 'A' && temp <= 'Z')
                            {
                                if (*firstSets[temp].begin() == '#')
                                {
                                    for (auto g : firstSets[temp])
                                    {
                                        if (g == '#')
                                            continue;
                                        followSets[r[i]].insert(g);
                                    }
                                    j++;
                                    if (j < r.size())
                                    {
                                        temp = r[j];
                                        if (!(temp >= 'A' && temp <= 'Z'))
                                        {
                                            followSets[r[i]].insert(temp);
                                            break;
                                        }
                                    }
                                    else
                                    {
                                        for (auto g : followSets[q.first])
                                            followSets[r[i]].insert(g);
                                        break;
                                    }
                                }
                                else
                                {
                                    for (auto g : firstSets[temp])
                                    {
                                        followSets[r[i]].insert(g);
                                    }
                                    break;
                                }
                            }
                        }
                    }
                }
                if (r[r.size() - 1] >= 'A' && r[r.size() - 1] <= 'Z')
                {
                    for (auto g : followSets[q.first])
                        followSets[r[i]].insert(g);
                }
            }
        }
    }

    return followSets;
}

bool isLL1(const map<char, set<char>> &firstSets, const map<char, set<char>> &followSets, const map<char, vector<vector<char>>> &grammar)
{
    for (const auto &entry : grammar)
    {
        char nonTerminal = entry.first;
        set<char> firstUnion;

        for (const auto &production : entry.second)
        {
            set<char> currentFirstSet;
            for (const auto &symbol : production)
            {
                if (symbol >= 'A' && symbol <= 'Z')
                {
                    const auto &subFirstSet = firstSets.at(symbol);
                    currentFirstSet.insert(subFirstSet.begin(), subFirstSet.end());
                    if (!subFirstSet.count('#'))
                    {
                        break;
                    }
                }
                else
                {
                    currentFirstSet.insert(symbol);
                    break;
                }
            }

            set<char> intersection;
            set_intersection(firstUnion.begin(), firstUnion.end(), currentFirstSet.begin(), currentFirstSet.end(), inserter(intersection, intersection.begin()));
            if (!intersection.empty())
            {
                return false;
            }

            firstUnion.insert(currentFirstSet.begin(), currentFirstSet.end());
        }

        if (firstUnion.count('#'))
        {
            set<char> intersection;
            set_intersection(firstUnion.begin(), firstUnion.end(), followSets.at(nonTerminal).begin(), followSets.at(nonTerminal).end(), inserter(intersection, intersection.begin()));
            if (!intersection.empty())
            {
                return false;
            }
        }
    }

    return true;
}

int main()
{ 
    cout<<"Mohd Siddiqul Haque 21bcs037"<<endl;
    map<char, vector<vector<char>>> grammar = readGrammar("Input.txt");

    eliminateLeftRecursion(grammar);

    map<char, set<char>> firstSets;
    for (const auto &entry : grammar)
    {
        getFirstSet(entry.first, grammar, firstSets);
    }

    char startSymbol = start;
    map<char, set<char>> followSets = calculateFollowSets(grammar, startSymbol, firstSets);

    bool ll1Compatible = isLL1(firstSets, followSets, grammar);

    if (ll1Compatible)
    {
        cout << "Given CFG is suitable for LL(1) parsing." << endl;
    }
    else
    {
        cout << "Given CFG is not suitable for LL(1) parsing as First & Follow have no common elements." << endl;
    }

    cout << "\nFIRST sets:" << endl;
    for (const auto &entry : firstSets)
    {
        cout << entry.first << " = { ";
        for (const auto &s : entry.second)
        {
            cout << s << " ";
        }
        cout << "}" << endl;
    }

    cout << "\nFOLLOW sets:" << endl;
    for (const auto &entry : followSets)
    {
        cout << entry.first << " = { ";
        for (const auto &s : entry.second)
        {
            cout << s << " ";
        }
        cout << "}" << endl;
    }

    return 0;
}