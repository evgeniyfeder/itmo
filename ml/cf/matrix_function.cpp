#include <iostream>
#include <utility>
#include <vector>
#include <cassert>
#include <map>
#include <memory>
#include <cmath>
#include <string>

struct matrix_t
{
    std::size_t h, w;
    std::vector<std::vector<double>> matrix;


    explicit matrix_t(std::size_t h = 0, std::size_t w = 0, double v = 0)
      : h(h), w(w)
    {
        matrix.resize(h, std::vector<double>(w, v));
    }

    void feel_input()
    {
        for (std::size_t i = 0; i < h; i++)
            for (std::size_t j = 0; j < w; j++)
                std::cin >> matrix[i][j];
    }

    void out_matrix()
    {
        std::cout.precision(10);

        for (std::size_t i = 0; i < h; i++)
        {
            for (std::size_t j = 0; j < w; j++)
                std::cout << matrix[i][j] << " ";
            std::cout << std::endl;
        }
    }
};

matrix_t operator*(matrix_t const & a, matrix_t const & b)
{
    assert(a.w == b.h);

    matrix_t c(a.h, b.w);
    for (std::size_t i = 0; i < c.h; i++)
        for (std::size_t j = 0; j < c.w; j++)
            for (std::size_t k = 0; k < a.w; k++)
                c.matrix[i][j] += a.matrix[i][k] * b.matrix[k][j];
    return c;
}

struct node_t
{
    matrix_t value;
    matrix_t derivative;

    virtual void eval() = 0;
    virtual void back_prop() = 0;

    void resize_derivative()
    {
        derivative = matrix_t(value.h, value.w);
    }
};

struct var_node_t : public node_t
{
    std::size_t index;

    explicit var_node_t(std::size_t index, std::size_t w, std::size_t h) : index(index)
    {
        value = matrix_t(h, w);
    }

    void eval() override
    {
    }

    void back_prop() override
    {
    }

};

struct tnh_node_t : public node_t
{
    std::shared_ptr<node_t> x;

    explicit tnh_node_t(std::shared_ptr<node_t>  x) : x(std::move(x))
    {}

    void eval() override
    {
        value = matrix_t(x->value.h, x->value.w);

        for (std::size_t i = 0; i < value.h; i++)
            for (std::size_t j = 0; j < value.w; j++)
                value.matrix[i][j] = std::tanh(x->value.matrix[i][j]);
    }

    void back_prop() override
    {
        for (std::size_t i = 0; i < x->derivative.h; i++)
            for (std::size_t j = 0; j < x->derivative.w; j++)
                x->derivative.matrix[i][j] += (1 - value.matrix[i][j] * value.matrix[i][j]) * derivative.matrix[i][j];
    }
};

struct rlu_node_t : public node_t
{
    std::shared_ptr<node_t> x;
    std::size_t a;

    rlu_node_t(std::shared_ptr<node_t>  x, std::size_t a) : x(std::move(x)), a(a) {}

    void eval() override
    {
        value = matrix_t(x->value.h, x->value.w);

        for (std::size_t i = 0; i < value.h; i++)
            for (std::size_t j = 0; j < value.w; j++)
                if (x->value.matrix[i][j] < 0)
                    value.matrix[i][j] = x->value.matrix[i][j] / static_cast<double>(a);
                else
                    value.matrix[i][j] = x->value.matrix[i][j];
    }

    void back_prop() override
    {
        for (std::size_t i = 0; i < value.h; i++)
            for (std::size_t j = 0; j < value.w; j++)
                if (x->value.matrix[i][j] >= 0)
                    x->derivative.matrix[i][j] += derivative.matrix[i][j];
                else
                    x->derivative.matrix[i][j] += derivative.matrix[i][j] / static_cast<double>(a);


    }
};

struct mul_node_t : public node_t
{
    std::shared_ptr<node_t> a, b;

    mul_node_t(std::shared_ptr<node_t> a, std::shared_ptr<node_t> b) : a(std::move(a)), b(std::move(b)) {}

    void eval() override
    {
        value = a->value * b->value;
    }

    void back_prop() override
    {
        std::size_t n = a->value.h, l = a->value.w, m = b->value.w;
        for (std::size_t i = 0; i < n; i++)
            for (std::size_t j = 0; j < l; j++)
                for (std::size_t k = 0; k < m; k++)
                    a->derivative.matrix[i][j] += derivative.matrix[i][k] * b->value.matrix[j][k];


        for (std::size_t i = 0; i < l; i++)
            for (std::size_t j = 0; j < m; j++)
                for (std::size_t k = 0; k < n; k++)
                    b->derivative.matrix[i][j] += a->value.matrix[k][i] * derivative.matrix[k][j];
    }
};

struct sum_node_t : public node_t
{
    std::vector<std::shared_ptr<node_t>> values;

    explicit sum_node_t(std::vector<std::shared_ptr<node_t>> values) : values(std::move(values)) {}

    void eval() override
    {
        matrix_t c(values[0]->value.h, values[0]->value.w);

        for (std::size_t matr = 0; matr < values.size(); matr++)
            for (std::size_t i = 0; i < c.h; i++)
                for (std::size_t j = 0; j < c.w; j++)
                    c.matrix[i][j] += values[matr]->value.matrix[i][j];
        value = c;
    }

    void back_prop() override
    {
        for (std::size_t matr = 0; matr < values.size(); matr++)
            for (std::size_t i = 0; i < derivative.h; i++)
                for (std::size_t j = 0; j < derivative.w; j++)
                    values[matr]->derivative.matrix[i][j] += derivative.matrix[i][j];
    }
};

struct had_node_t : public node_t
{
    std::vector<std::shared_ptr<node_t>> values;

    explicit had_node_t(std::vector<std::shared_ptr<node_t>> values) : values(std::move(values)) {}

    void eval() override
    {
        matrix_t c(values[0]->value.h, values[0]->value.w, 1);
        for (std::size_t matr = 0; matr < values.size(); matr++)
            for (std::size_t i = 0; i < c.h; i++)
                for (std::size_t j = 0; j < c.w; j++)
                    c.matrix[i][j] *= values[matr]->value.matrix[i][j];
        value = c;
    }

    void back_prop() override
    {
        for (std::size_t matr = 0; matr < values.size(); matr++)
            for (std::size_t i = 0; i < value.h; i++)
                for (std::size_t j = 0; j < value.w; j++)
                {
                    double mult = 1;
                    for (std::size_t matr2 = 0; matr2 < values.size(); matr2++)
                    {
                        if (matr != matr2)
                            mult *= values[matr2]->value.matrix[i][j];
                    }
                    values[matr]->derivative.matrix[i][j] += mult * derivative.matrix[i][j];
                }
    }
};

int main()
{
#ifdef LOCAL
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
#endif

    std::size_t n, in_cnt, out_cnt;
    std::cin >> n >> in_cnt >> out_cnt;

    std::vector<std::shared_ptr<node_t>> nodes;

    for (std::size_t i = 0; i < n; i++)
    {
        std::string op;
        std::cin >> op;

        if (op == "var")
        {
            std::size_t w, h;
            std::cin >> h >> w;
            nodes.push_back(std::make_shared<var_node_t>(i, w, h));
        }
        else if (op == "tnh")
        {
            std::size_t x;
            std::cin >> x;
            nodes.push_back(std::make_shared<tnh_node_t>(nodes[x - 1]));
        }
        else if (op == "rlu")
        {
            std::size_t alpha, x;
            std::cin >> alpha >> x;
            nodes.push_back(std::make_shared<rlu_node_t>(nodes[x - 1], alpha));
        }
        else if (op == "mul")
        {
            std::size_t a, b;
            std::cin >> a >> b;
            nodes.push_back(std::make_shared<mul_node_t>(nodes[a - 1], nodes[b - 1]));
        }
        else if (op == "sum")
        {
            std::vector<std::shared_ptr<node_t>> nodes_local;

            std::size_t num;
            std::cin >> num;

            for (std::size_t matr_i = 0; matr_i < num; matr_i++)
            {
                std::size_t x;
                std::cin >> x;
                nodes_local.push_back(nodes[x - 1]);
            }
            nodes.push_back(std::make_shared<sum_node_t>(nodes_local));
        }
        else if (op == "had")
        {
            std::vector<std::shared_ptr<node_t>> nodes_local;

            std::size_t num;
            std::cin >> num;

            for (std::size_t matr_i = 0; matr_i < num; matr_i++)
            {
                std::size_t x;
                std::cin >> x;
                nodes_local.push_back(nodes[x - 1]);
            }
            nodes.push_back(std::make_shared<had_node_t>(nodes_local));
        }
        else
        {
            assert(":(");
        }
    }

    for (std::size_t i = 0; i < in_cnt; i++)
        nodes[i]->value.feel_input();

    for (std::size_t i = 0; i < n; i++)
        nodes[i]->eval();

    for (std::size_t i = n - out_cnt; i < n; i++)
    {
        nodes[i]->derivative = matrix_t(nodes[i]->value.h, nodes[i]->value.w);
        nodes[i]->derivative.feel_input();
        nodes[i]->value.out_matrix();
    }

    for (std::size_t i = 0; i < n - out_cnt; i++)
        nodes[i]->resize_derivative();

    for (std::int32_t i = n - 1; i >= 0; i--)
        nodes[i]->back_prop();

    for (std::size_t i = 0; i < in_cnt; i++)
        nodes[i]->derivative.out_matrix();

}
