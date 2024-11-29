#include "gameboard.h"
#include <random>

namespace
{
    bool isAdjacent(const GameBoard::Position f, const GameBoard::Position s)
    {
        // Эта функция проверяет соседние ли две позиции
        // Сравниваем эти позиции
        if (f == s)
            return false;
        // Если разные, посчитаем расстояние между ними
        const auto calcDistance = [](const size_t pos1, const size_t pos2){
            int distance = static_cast<int>(pos1);
            distance -= static_cast<int>(pos2);
            distance = std::abs(distance);
            return distance;
        };
        bool result {false};

        if (f.first == s.first) // Позиции находятся на одной строке
        {
            auto distance = calcDistance(f.second, s.second);
            if (distance == 1)
                result = true;
        }
        else if (f.second == s.second)
        {
            auto distance = calcDistance(f.first, s.first);
            if (distance == 1)
                result = true;
        }

        return result;
    }
}
GameBoard::GameBoard(const size_t boardDimension, QObject* parent)
    : QAbstractListModel {parent},
    m_dimension {boardDimension},
    m_boardSize {m_dimension * m_dimension}
{
    m_rawBoard.resize(m_boardSize);
    for (size_t i = 0; i < m_boardSize; ++i)
    {
        Tile t;
        t.value = i + 1;
        m_rawBoard[i] = t;
    }
    Shuffle();
}

int GameBoard::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_rawBoard.size();
}

QVariant GameBoard::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
        return {};

    int rowIndex {index.row()};

    if (!isPositionValid(rowIndex))
        return {};

    return QVariant::fromValue(m_rawBoard[rowIndex].value);
}

size_t GameBoard::boardSize() const
{
    return m_boardSize;
}

bool GameBoard::move(int index)
{
    if (!isPositionValid(static_cast<size_t>(index)))
        return false;

    const Position elementPosition = getRowCol(index);
    // Позиция кликнутой ячейки найдена
    // Найдем скрытый элемент. Бежим по вектору из <Tile>
    auto hiddenElementIterator = std::find(m_rawBoard.begin(), m_rawBoard.end(), boardSize());
    // и сравниваем с m_boardSize. Это сработает, так как
    // переопределили оператор сравнения ==
    Q_ASSERT(hiddenElementIterator != m_rawBoard.end());
    Position hiddenElementPosition = getRowCol(std::distance(m_rawBoard.begin(), hiddenElementIterator));

    if (!isAdjacent(elementPosition,hiddenElementPosition))
    {
        return false;
    }
    auto elementIterator = m_rawBoard.begin() + index;
    Q_ASSERT(elementIterator != m_rawBoard.end());
    std::iter_swap(hiddenElementIterator,elementIterator);
    emit dataChanged(createIndex(0,0),createIndex(m_boardSize,0));
    return true;
}

GameBoard::Position GameBoard::getRowCol(const size_t index)
{
    Q_ASSERT(m_dimension > 0);
    size_t row = index / m_dimension;
    size_t col = index % m_dimension;
    return std::make_pair(row, col);
}

size_t GameBoard::dimension() const
{
    return m_dimension;
}

void GameBoard::Shuffle()
{
    static auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::mt19937 generator(seed); // Генератор из <random>
    std::shuffle(m_rawBoard.begin(), m_rawBoard.end(), generator);
}

bool GameBoard::isPositionValid(const size_t position) const
{
    return position < m_boardSize;
}
