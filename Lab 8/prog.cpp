#include <bits/stdc++.h>
#include <unordered_map>
#include <set>
#include <vector>
#include <fstream>

using namespace std;

unordered_map<char, set<char>> FIRST, FOLLOW;
unordered_map<char, vector<string>> productions;
unordered_map<char, unordered_map<char, string>> parsingTable;
vector<char> terminals;
char startSymbol = '\0';

void readTxt();
void calculateFIRST(char);
void calculateFOLLOW(char);
void printFirstFollow();
void terminalSet();
void constructParsingTable();
void printParsingTable();
void parseInput(string &input);


void readTxt()
{
  fstream myfile;
  myfile.open("Input.txt", ios::in);
  string line;
  cout << "\nCFG:\n\n";
  while (getline(myfile, line))
  {
    cout << line << endl;
    int equalPos = line.find("->"); // Find the position of '='
    if (equalPos != string::npos)
    {
      char NT = line[0];
      if (startSymbol == '\0')
      {
        startSymbol = line[0]; // Set the starting symbol
      }
      string production = line.substr(equalPos + 2); // Get the substring after '->'
      int pos = 0;
      string token;
      while (production.find('|') != string::npos)
      {
        pos = production.find('|');
        token = production.substr(0, pos);
        productions[NT].push_back(token);
        production.erase(0, pos + 1);
      }
      productions[NT].push_back(production); // Add the last or only production
    }
  }
  cout << endl;
  myfile.close();
}

void terminalSet()
{
  for (auto prod : productions)
  {
    for (string str : prod.second)
    {
      for (int i = 0; i < str.size(); i++)
      {
        if (!isupper(str[i]))
        {
          terminals.push_back(str[i]);
        }
      }
    }
  }

  sort(terminals.begin(), terminals.end());
  terminals.erase(unique(terminals.begin(), terminals.end()), terminals.end());
  terminals.erase(remove(terminals.begin(), terminals.end(), ' '), terminals.end());
  terminals.push_back('$');
}

void calculateFIRST(char NT)
{
  if (!FIRST[NT].empty())
    return; // Already calculated
  int flag = 0;

  for (string &prod : productions[NT])
  {
    int len = prod.size();
    int i = 0;
    for (char symbol : prod)
    {
      if (isupper(symbol))
      { // Non-terminal
        len--;
        calculateFIRST(symbol);
        FIRST[NT].insert(FIRST[symbol].begin(), FIRST[symbol].end());
        FIRST[NT].erase('#'); // remove epsilon
        if (FIRST[symbol].find('#') == FIRST[symbol].end())
        {
          flag = 1;
          break;
        }
        if (flag == 0 && len == 0)
        {
          FIRST[NT].insert('#'); // if RHS is all epsilon then add epsilon
        }
      }
      else
      { // Terminal or Epsilon
        FIRST[NT].insert(symbol);
        break;
      }
    }
  }
}

void calculateFOLLOW(char NT)
{
  if (!FOLLOW[NT].empty())
    if (NT != startSymbol)
    {
      return; // Already calculated
    }
  for (auto &prod : productions)
  {
    for (string &str : prod.second)
    {
      for (int i = 0; i < str.size(); ++i)
      {
        if (str[i] == NT)
        {
          int j = i + 1;
          while (j < str.size())
          {
            char nextSymbol = str[j];
            if (isupper(nextSymbol))
            { // Next is a Non-terminal
              FOLLOW[NT].insert(FIRST[nextSymbol].begin(), FIRST[nextSymbol].end());
              FOLLOW[NT].erase('#'); // Remove Epsilon if it's there
              if (j == str.size() - 1 && FIRST[nextSymbol].find('#') != FIRST[nextSymbol].end())
              {
                calculateFOLLOW(prod.first);
                FOLLOW[NT].insert(FOLLOW[prod.first].begin(), FOLLOW[prod.first].end());
              }
              else if (FIRST[nextSymbol].find('#') == FIRST[nextSymbol].end())
              {
                break;
              }
            }
            else
            { // Next is a Terminal
              FOLLOW[NT].insert(nextSymbol);
            }
            j++;
          }
          if (prod.first != NT && i + 1 >= str.size())
          {
            calculateFOLLOW(prod.first);
            FOLLOW[NT].insert(FOLLOW[prod.first].begin(), FOLLOW[prod.first].end());
          }
        }
      }
    }
  }
}

void printFirstFollow()
{ // Calculate FIRST
  for (auto prod : productions)
  {
    calculateFIRST(prod.first);
  }

  // Calculate FOLLOW
  for (auto prod : productions)
  {
    calculateFOLLOW(prod.first);
  }

  cout << "FIRST OF NON-TERMINALS: " << endl
       << endl;
  for (auto &prod : productions)
  {
    cout << "FIRST(" << prod.first << ") = { ";
    for (char c : FIRST[prod.first])
    {
      cout << c << " ";
    }
    cout << "}" << endl;
  }
  cout << "\n------------------------------\n\n";
  cout << "FOLLOW OF NON-TERMINALS: " << endl
       << endl;
  for (auto &prod : productions)
  {
    cout << "FOLLOW(" << prod.first << ") = { ";
    for (char c : FOLLOW[prod.first])
    {
      cout << c << " ";
    }
    cout << "}" << endl;
  }
  cout << endl;
}

void constructParsingTable()
{
  for (auto &prod : productions)
  {
    char nonTerminal = prod.first;
    for (const string &prodStr : prod.second)
    {
      set<char> firstSet;
      for (char symbol : prodStr)
      {
        if (isupper(symbol))
        { // Non-terminal
          firstSet.insert(FIRST[symbol].begin(), FIRST[symbol].end());
          if (FIRST[symbol].find('#') == FIRST[symbol].end())
          {
            break;
          }
        }
        else
        { // Terminal or Epsilon
          firstSet.insert(symbol);
          break;
        }
      }
      for (char terminal : firstSet)
      {
        if (terminal != '#')
        {
          parsingTable[nonTerminal][terminal] = prodStr;
        }
        else
        {
          for (char follow : FOLLOW[nonTerminal])
          {
            parsingTable[nonTerminal][follow] = prodStr;
          }
        }
      }
    }
  }
}

void printParsingTable()
{
  cout << "LL(1) Parsing Table:\n\n";
  cout << "NT" << setw(15);
  for (const auto t : terminals)
  {
    if (t != '#')
    {
      cout << t << setw(17);
    }
  }
  cout << endl;
  cout << setw(0) << "--------------------------------------------------------------------------------------------------------" << endl;
  for (const auto &nonTerminalEntry : parsingTable)
  {
    char nonTerminal = nonTerminalEntry.first;
    const auto &terminalMap = nonTerminalEntry.second;
    cout << nonTerminal;
    for (const auto t : terminals)
    {
      // char terminal = terminalEntry.first;
      if (t != '#')
      {

        if (terminalMap.count(t))
        {
          const string &production = terminalMap.at(t);
          cout << setw(15) << nonTerminal << "->" << production;
        }
        else
        {
          cout << setw(15) << "-";
        }
      }
    }
    cout << endl;
  }
}

void parseInput(string &input)
{
  input += '$';
  stack<char> symbolStack;
  symbolStack.push('$');         // Push end of input marker
  symbolStack.push(startSymbol); // Push starting symbol

//   cout << "\nSteps involved:" << endl;

  int inputIndex = 0;
  char currentInput = input[inputIndex];

  cout << "\nStack: ";
  stack<char> printStack = symbolStack;
  while (!printStack.empty())
  {
    cout << printStack.top();
    printStack.pop();
  }

  cout << "\t\tInput: " << input.substr(inputIndex) << endl;

  while (!symbolStack.empty())
  {
    char stackTop = symbolStack.top();

    if (stackTop == currentInput && currentInput == '$')
    {
      cout << "\nSuccessfully this string is passed." << endl;
      return;
    }

    if (!isupper(stackTop))
    { // Terminal symbol
      if (stackTop == currentInput)
      {
        symbolStack.pop();
        inputIndex++;
        currentInput = input[inputIndex];
      }
      else
      {
        cout << "\nError:terminal symbol is not matching" << endl;
        return;
      }
    }
    else
    { // Non-terminal symbol
      auto it = parsingTable.find(stackTop);
      if (it != parsingTable.end())
      {
        auto &row = it->second;
        auto colIt = row.find(currentInput);
        if (colIt != row.end())
        {
          const string &production = colIt->second;
          cout << "\nUsing production rule: " << stackTop << " -> " << production << endl;

          // Pop the non-terminal from the stack
          symbolStack.pop();

          // Push the production rule in reverse order onto the stack
          for (auto rit = production.rbegin(); rit != production.rend(); ++rit)
          {
            if (*rit != '#')
            { // Skip epsilon
              symbolStack.push(*rit);
            }
          }
        }
        else
        {
          cout << "\nError: production rule is not found." << endl;
          break;
        }
      }
      else
      {
        cout << "\nError: production  rule is not found." << endl;
        break;
      }
    }

    // Print current stack and input
    cout << "Stack: ";
    stack<char> printStack = symbolStack;
    while (!printStack.empty())
    {
      cout << printStack.top();
      printStack.pop();
    }
    cout << "\t\tInput: " << input.substr(inputIndex) << endl;
  }

  cout << "\nParsing Failed." << endl;
}
int main()
{ 
  cout<<"Mohd Siddiqul Haque"<<endl;
  readTxt();
  FOLLOW[startSymbol].insert('$'); // Add $ to the FOLLOW of starting symbol
  printFirstFollow();
  terminalSet();
  constructParsingTable();
  printParsingTable();

  string input;
  cout << "\nEnter the input string to parse: ";
  cin >> input;
  parseInput(input);
  return 0;
}
