#include <vector>

class PatternGenerator
{
public:
    PatternGenerator(int channels, int minDuration, int maxDuration);
    std::vector<std::pair<int, int>> GetPattern();

private:
    int mChannels, mMinDuration, mMaxDuration;
    std::vector<std::pair<int, int>> mPattern;

    void ConstructPattern();
};
