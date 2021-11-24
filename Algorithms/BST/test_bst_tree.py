import unittest
import random
import string
from multiprocessing import Process, Queue, cpu_count
from rbtree import RedBlackTree
from avltree import AVLTree


class Request:
    def __init__(self, input, clazz):
        self.input = tuple(input)
        self.clazz = clazz

    def __hash__(self):
        return 37 * hash(self.input) + 29 * hash(self.clazz)

    def __repr__(self):
        return "Request(%s for %s)" % (self.input, self.clazz)


class Response:
    def __init__(self, id, ok, input=None, rinput=None, v=None, excep=None):
        self.id = id
        self.ok = ok
        self.input = input
        self.rinput = rinput
        self.v = v
        self.excep = excep

    def __repr__(self):
        if self.ok:
            return "%s: OK" % self.id
        else:
            return "%s\n%s\n%s\n%s" % (self.input, self.rinput, self.v, self.excep)


def get_hybrid_operations(input):
    class Operation:
        def __init__(self, key, inserting=True):
            self.key = key
            self.inserting = inserting

        def __repr__(self):
            return "%s %s" % ("insert" if self.inserting else "delete", self.key)

    retval = []
    deleting = []
    upper_limit = len(input)
    start = 0
    while start < upper_limit:
        end = min(start + 20, upper_limit)
        v = random.randint(start, end)
        if v == start:
            v += 1
        for i in range(start, v):
            retval.append(Operation(input[i]))
        deleting.extend(input[start:v])
        start = v
        dl = len(deleting)
        if dl > 0:
            v = random.randint(0, dl)
            if v == 0:
                v = 1
            for i in range(0, v):
                retval.append(Operation(deleting[i], False))
            deleting = deleting[v:]
    for v in deleting:
        retval.append(Operation(v, False))
    return retval


def run_case(request_queue, response_queue):
    while True:
        request = request_queue.get()
        id = hash(request)
        input = list(request.input)
        rinput = []
        v = None
        try:
            operations = get_hybrid_operations(input)
            tree = RedBlackTree() if request.clazz == "RedBlackTree" else AVLTree()
            for o in operations:
                if o.inserting:
                    successful = tree.put(o.key)
                    assert successful
                    assert o.key in tree
                else:
                    assert o.key in tree
                    del tree[o.key]
                    assert o.key not in tree

            for v in input:
                successful = tree.put(v)
                assert successful
                assert v in tree
                assert tree.valid()
            rinput = input[:]
            random.shuffle(rinput)
            for v in rinput:
                assert v in tree
                del tree[v]
                assert v not in tree
                assert tree.valid()
            r = Response(id, True)
            response_queue.put(r)
        except Exception as e:
            r = Response(id, False, input, rinput, v, e)
            response_queue.put(r)


class BSTTester(unittest.TestCase):
    def setUp(self):
        self.request_queue = Queue()
        self.response_queue = Queue()
        cpu = cpu_count()
        self.workers = [Process(target=run_case, args=(
            self.request_queue, self.response_queue)) for _ in range(cpu)]

    def test_trees(self):
        REPEAT = 32
        LOWER_LIMIT = 512
        UPPER_LIMIT = 1024*2
        case_number = 0
        lens = set()
        for _ in range(REPEAT):
            while True:
                l = random.randint(LOWER_LIMIT, UPPER_LIMIT)
                if l not in lens:
                    lens.add(l)
                    break
            input = [_ for _ in range(l)]
            r = Request(input, "RedBlackTree")
            self.request_queue.put(r)
            case_number += 1
            r = Request(input, "AVLTree")
            self.request_queue.put(r)
            case_number += 1

            input.reverse()
            r = Request(input, "RedBlackTree")
            self.request_queue.put(r)
            case_number += 1
            r = Request(input, "AVLTree")
            self.request_queue.put(r)
            case_number += 1

            random.shuffle(input)
            r = Request(input, "RedBlackTree")
            self.request_queue.put(r)
            case_number += 1
            r = Request(input, "AVLTree")
            self.request_queue.put(r)
            case_number += 1

            random.shuffle(input)
            r = Request(input, "RedBlackTree")
            self.request_queue.put(r)
            case_number += 1
            r = Request(input, "AVLTree")
            self.request_queue.put(r)
            case_number += 1

        for w in self.workers:
            w.start()

        wrong = False
        for _ in range(case_number):
            r = self.response_queue.get()
            if not r.ok:
                print(r)
                wrong = True

        for w in self.workers:
            w.terminate()

        self.request_queue.close()
        self.response_queue.close()

        self.assertFalse(wrong)

    def generate_random_strings(self):
        N = 1024 * 2
        L = 16
        retval = set()
        for _ in range(N):
            letters = string.ascii_lowercase
            retval.add(''.join(random.choice(letters) for i in range(L)))
        return sorted(list(retval))

    def test_indexable(self):
        strings = self.generate_random_strings()
        N = len(strings)
        rdata = strings[:]
        random.shuffle(rdata)
        tree = RedBlackTree()
        for r in rdata:
            tree.put(r)
            self.assertTrue(r in tree)
            self.assertTrue(tree.valid())
        for i in range(N):
            self.assertEqual(tree[i], strings[i])
        self.assertEqual(list(tree), strings)
        to_be_deleted = strings[:]
        for i in range(N - 1):
            j = random.randint(0, N - 1 - i)
            s = to_be_deleted.pop(j)
            self.assertEqual(tree[j], s)
            del tree[s]
            self.assertFalse(s in tree)
