#pragma once

#include <string>
#include <vector>

class Symbol
{
public:
    Symbol(size_t id, const std::string& name, const std::vector<size_t>& pays);
    size_t GetPay(size_t reels) const;
    size_t GetID() const;
    std::string GetName() const;
    size_t GetReelsCount() const;
    bool operator==(const Symbol& symbol) const;
private:
    size_t m_id = 0;
    std::string m_name;
    std::vector<size_t> m_pays;
};

class Symbols
{
public:
    void AddSymbol(double rarity, const Symbol& symbol);
    Symbol const& GetRandomSymbol() const;
private:
    std::vector<std::pair<double, Symbol>> m_symbols;
};