/*
 * TASK: You are given an image represented as a two-dimensional array (a
 *       matrix) of pixels, with each one of them being painted with some color.
 *       Implement the flood-fill algorithm for painting the image, i.e., given
 *       a pixel and a color, paint all pixels in the color region to which this
 *       pixel belongs with the given color.
 */

#include <algorithm>
#include <cassert>
#include <deque>
#include <iostream>
#include <queue>
#include <random>

enum color
{
    RED = 0,
    GREEN,
    BLUE,
    TOTAL_NUM_COLORS
};

/** @brief A matrix-like class for representing pixels on an image. */
template<typename T>
class pixels
{
public:
    pixels(const size_t width, const size_t height)
        : width_(width),
          height_(height),
          entries_(width, std::deque<T>(height, T{}))
    {
        /* nothing needs to be done here */
    }

    size_t width() const
    {
        return width_;
    }

    size_t height() const
    {
        return height_;
    }

    T& operator()(const size_t i, const size_t j)
    {
        return entries_[i][j];
    }

    bool operator==(const pixels& other) const
    {
        return (*this).entries_ == other.entries_;
    }

private:
    const size_t width_;
    const size_t height_;

    /*
     * an std::deque is used instead of std::vector because we want T to
     * be allowed to be bool, but operator() would not be able to return a
     * T& if we used std::vector
     */
    std::deque<std::deque<T> > entries_;
};

/* an image is just a collection of pixels with assigned colors */
using image = pixels<color>;

void __paint_fill_1(image& I,
                    const size_t i,
                    const size_t j,
                    const color new_color,
                    const color original_color)
{
    assert(i < I.width() && j < I.height());

    if (I(i, j) != original_color)
    {
        return;
    }

    I(i, j) = new_color;

    /*
     * try to continue painting along every valid direction: left, right,
     * bottom and top
     */
    if (i > 0)
    {
        __paint_fill_1(I, i - 1, j, new_color, original_color);
    }
    if (i + 1 < I.width())
    {
        __paint_fill_1(I, i + 1, j, new_color, original_color);
    }
    if (j > 0)
    {
        __paint_fill_1(I, i, j - 1, new_color, original_color);
    }
    if (j + 1 < I.height())
    {
        __paint_fill_1(I, i, j + 1, new_color, original_color);
    }
}

/**
 * @brief Paints the color region to which the pixel (i,j) on an image I belongs
 *        with a new color using recursive flood fill (depth-first search).
 * @note Complexity: O(m*n) in both time and space, where m and n are the image
 *       width and height respectively.
 */
void paint_fill_1(image& I,
                  const size_t i,
                  const size_t j,
                  const color new_color)
{
    /* if the image has zero area, do nothing */
    if (I.width() == 0 || I.height() == 0)
    {
        return;
    }

    /*
     * if we are painting at (i,j) using the same color which (i,j)
     * already has, do nothing (otherwise we would have an endless loop
     * if we painted, say, a black region with more than one pixel
     * using the black color)
     */
    if (new_color == I(i, j))
    {
        return;
    }

    __paint_fill_1(I, i, j, new_color, I(i, j));
}

void __paint_fill_2(image& I,
                    const size_t i,
                    const size_t j,
                    const color new_color,
                    const color original_color)
{
    assert(i < I.width() && j < I.height());

    struct pixel
    {
        size_t x;
        size_t y;
    };

    std::queue<pixel> Q;

    pixels<bool> explored(I.width(), I.height());

    Q.push({i, j});
    explored(i, j) = true;

    /*
     * invariant: all pixels stored on Q belong to the same color region
     * to which (i,j) originally belonged
     */
    while (Q.empty() == false)
    {
        const pixel R = Q.front();
        Q.pop();

        I(R.x, R.y) = new_color;

        /* should we paint: right, left, top, bottom? */
        if (R.x + 1 < I.width() && I(R.x + 1, R.y) == original_color &&
            explored(R.x + 1, R.y) == false)
        {
            Q.push(pixel{R.x + 1, R.y});
            explored(R.x + 1, R.y) = true;
        }
        if (R.x > 0 && I(R.x - 1, R.y) == original_color &&
            explored(R.x - 1, R.y) == false)
        {
            Q.push(pixel{R.x - 1, R.y});
            explored(R.x - 1, R.y) = true;
        }
        if (R.y + 1 < I.height() && I(R.x, R.y + 1) == original_color &&
            explored(R.x, R.y + 1) == false)
        {
            Q.push(pixel{R.x, R.y + 1});
            explored(R.x, R.y + 1) = true;
        }
        if (R.y > 0 && I(R.x, R.y - 1) == original_color &&
            explored(R.x, R.y - 1) == false)
        {
            Q.push(pixel{R.x, R.y - 1});
            explored(R.x, R.y - 1) = true;
        }
    }
}

/**
 * @brief Paints the color region to which the pixel (i,j) on an image I belongs
 *        with a new color using iterative flood fill (breadth-first search).
 * @note Complexity: O(m*n) in both time and space, where m and n are the image
 *       width and height respectively.
 */
void paint_fill_2(image& I,
                  const size_t i,
                  const size_t j,
                  const color new_color)
{
    /* if the image has zero area, do nothing */
    if (I.width() == 0 || I.height() == 0)
    {
        return;
    }

    __paint_fill_2(I, i, j, new_color, I(i, j));
}

/**
 * @brief Generates a random color.
 * @note Complexity: O(1) in both time and space.
 */
color random_color()
{
    static std::random_device device;
    static std::mt19937 generator(device());

    std::uniform_int_distribution<int> color_chooser(0, TOTAL_NUM_COLORS - 1);

    return static_cast<color>(color_chooser(generator));
}

/**
 * @brief Generates a random image with width m and height n.
 * @note Complexity: O(m*n) in both time and space.
 */
image random_image(const size_t m, const size_t n)
{
    image I(m, n);

    for (size_t i = 0; i < m; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            I(i, j) = random_color();
        }
    }

    return I;
}

int main()
{
    std::random_device device;
    std::mt19937 generator(device());

    size_t max_size = 10;

    for (size_t m = 0; m <= max_size; ++m)
    {
        for (size_t n = 0; n <= max_size; ++n)
        {
            for (int k = 0; k < 100; ++k)
            {
                image I = random_image(m, n);

                image I1 = I;
                image I2 = I;

                /*
                 * paint 10 randomly chosen pixels (same for both I1
                 * and I2) with randomly chosen colors using the two
                 * flood-fill approaches, and make sure the two images
                 * always remain equal as they are painted
                 */
                if (m > 0 && n > 0)
                {
                    std::uniform_int_distribution<size_t> pixel_i(0, m - 1);
                    std::uniform_int_distribution<size_t> pixel_j(0, n - 1);

                    for (size_t p = 0; p < 10; ++p)
                    {
                        size_t i = pixel_i(generator);
                        size_t j = pixel_j(generator);

                        color c = random_color();

                        paint_fill_1(I1, i, j, c);
                        paint_fill_2(I2, i, j, c);

                        assert(I1 == I2);
                    }
                }
            }

            std::cout << "passed random tests for images of size " << m << "×"
                      << n << std::endl;
        }
    }

    return EXIT_SUCCESS;
}
