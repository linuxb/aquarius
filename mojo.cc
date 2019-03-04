#include <iostream>

#define KSWAP(a, b, T) \
  do {  \
    T temp = a;  \
    (a) = b;  \
    (b) = temp; \
  } while(0);

template <typename T>
static int partition(T arr[], int l, int r) {
  int i = l - 1;
  T pivot = arr[r];
  for (int j = l; j < r; ++j) {
    if (arr[j] < pivot) {
      i++;
      KSWAP(arr[i], arr[j], T);
    }
  }
  i++;
  KSWAP(arr[i], arr[r], T);
  return i;
}

template <typename T>
static void qs_opt(T arr[], int l, int r) {
  if (l >= r) return;
  int m = partition<T>(arr, l, r);
  qs_opt<T>(arr, l, m - 1);
  qs_opt<T>(arr, m + 1, r);
}

static void test_qs_opt() {
  float karr[] = {2.9, 6.7, 8.32, 1, 5, 0, 3};
  qs_opt(karr, 0, 6);
  for (auto x : karr) {
    printf("%.2f, ", x);
  }
  printf("\n");
}

namespace mojo {
    template <typename T, T ...Elems>
    struct list;

    template <typename T, T ...Elems>
    struct foreach_t {};

    // yield the first one
    template <typename T, T Head, T ...Tails>
    struct foreach_t<list<T, Head, Tails...>> {
        template <typename Fn>
        static void apply(Fn functor) {
          functor(Head);
          foreach_t<list<T, Tails...>>::apply(functor);
        }
    };

    template <typename T>
    struct foreach_t<list<T>> {
        template <typename Fn>
        static void apply(Fn f) {}
    };

    struct task_t {
        template <typename T>
        void operator()(T x) {
          printf("%d, ", x);
        }
    };

    template <typename L, typename Fn>
    static void foreach(Fn f = Fn()) {
      foreach_t<L>::apply(f);
    }

    template <typename ...T>
    struct concat;

    template <typename T, T ...L1, T ...L2, typename ...Rest>
    struct concat<list<T, L1...>, list<T, L2...>, Rest...> {
        typedef list<T, L1..., L2...> nl;
        typedef typename concat<nl, Rest...>::type type;
    };

    template <typename T, T ...Elems>
    struct concat<list<T, Elems...>> {
        typedef list<T, Elems...> type;
    };

    template <bool Cond, typename T, typename F>
    struct if_else {
        typedef T type;
    };

    template <typename T, typename F>
    struct if_else<false, T, F> {
        typedef F type;
    };

    template <template <typename U, U> class K, typename T>
    struct filter;

    template <template <typename U, U> class K,
            typename T, T Cur, T ...Rest>
    struct filter<K, list<T, Cur, Rest...>> {
        typedef typename filter<K, list<T, Rest...>>::type rest_t;
        typedef list<T, Cur> cur_t;
        typedef typename if_else<K<T, Cur>::value,
                typename concat<cur_t, rest_t>::type,
                rest_t>::type type;
    };

    template <template <typename U, U> class K, typename T>
    struct filter<K, list<T>> {
        typedef list<T> type;
    };

    template <typename T, T t>
    struct is_odd
    {
        static const bool value = t & T(1);
    };

    static void RunListOp() {
      typedef list<int, 3, 5, 7, 8> xs_t;
      typedef list<int, 4, 5, 7> ys_t;
      foreach<concat<xs_t, ys_t>::type, task_t>();
      typedef list<int, 8, 9, 2, 1, 0, 23, 11, 23, 3, 512 > zs_t;
      foreach<filter<is_odd, zs_t>::type, task_t>();
    }
}

static void Run() {
  mojo::RunListOp();
}

int main() {
  auto k = std::move(6);
  std::cout << "res: " << k << "\n";
  test_qs_opt();
  Run();
  return 0;
}