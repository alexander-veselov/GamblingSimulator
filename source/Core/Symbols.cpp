#include "Symbols.h"

#include <assert.h>
#include <random>

namespace
{

constexpr int kMinimumReelsCount = 3;

double GetRandomNumber_Exponential()
{
    static std::random_device dev;
    static std::mt19937 rng(dev());
    static std::exponential_distribution<> distr(1.0);
    return distr(rng);
}

double GetRandomNumber_Uniform()
{
    static std::random_device dev;
    static std::mt19937 rng(dev());
    static std::uniform_real_distribution<> distr(0.0, 1.0);
    return distr(rng);
}

}

Symbol::Symbol(size_t id, const std::string& name, const std::vector<size_t>& pays) :
    m_id(id), m_name(name), m_pays(pays)
{}

size_t Symbol::GetID() const
{
    return m_id;
}

std::string Symbol::GetName() const
{
    return m_name;
}

size_t Symbol::GetPay(size_t reels) const
{
    assert(reels >= kMinimumReelsCount);
    if (reels < kMinimumReelsCount)
        return 0;
    return m_pays[reels - kMinimumReelsCount];
}

size_t Symbol::GetReelsCount() const
{
    return m_pays.size() + kMinimumReelsCount - 1;
}

bool Symbol::operator==(const Symbol& symbol) const
{
    return m_id == symbol.m_id;
}

void Symbols::AddSymbol(double rarity, const Symbol& symbol)
{
    m_symbols.push_back({ rarity, symbol });
}

Symbol const& Symbols::GetRandomSymbol() const
{
    assert(!m_symbols.empty());
    if (m_symbols.empty())
        std::terminate();

    size_t symbolIndex = 0;
    double left = 0;
    double right = m_symbols[0].first;
    
    double randomNumber = GetRandomNumber_Uniform();
    for (size_t i = 1; i < m_symbols.size(); ++i)
    {
        left = right;
        right += m_symbols[i].first;
        
        if (left <= randomNumber && randomNumber < right)
        {
            symbolIndex = i;   
        }
    }
    assert(std::fabs(right - 1.0) < 0.01);
    return m_symbols[symbolIndex].second;
}

