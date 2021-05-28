import java.util.*;

public class Trie<V>
{
    static class Node<V> {
        V value = null;
        Map<Character, Node<V>> children = new HashMap<>();
    }

    private Node<V> root;
    private int size;

    public Trie() {
        root = new Node<V>();
        size = 0;
    }

    public void clear() {
        root = null;
        size = 0;
    }

    static class SearchResult<V> {
        Node<V> selfOrParent;
        int index;
        int indexOfLongestPrefix;

        SearchResult(Node<V> n, int i, int ilp) {
            selfOrParent = n;
            index = i;
            indexOfLongestPrefix = ilp;
        }
    }

    private static<V> SearchResult<V> search(
        Node<V> root,
        String s,
        boolean allowedToCreateNew
    ) {
        assert(root != null);
        Node<V> selfOrParent = root;
        int indexOfLongestPrefix = 0;
        int i;
        for (i = 0; i < s.length(); ++i) {
            Character c = Character.valueOf(s.charAt(i));
            Node<V> grandchildren = selfOrParent.children.get(c);
            if (grandchildren != null) {
                selfOrParent = grandchildren;
                if (selfOrParent.value != null && (i + 1) < s.length()) {
                    indexOfLongestPrefix = i;
                }
            } else {
                if (allowedToCreateNew) {
                    grandchildren = new Node<V>();
                    selfOrParent.children.put(c, grandchildren);
                    selfOrParent = grandchildren;
                }
            }
        }
        return new SearchResult<>(selfOrParent, i, indexOfLongestPrefix);
    }

    public void put(String key, V value) {
        var result = search(root, key, true);
        if (result.selfOrParent.value == null) {
            ++size;
        }
        result.selfOrParent.value = value;
    }

    public V get(String key) {
        var result = search(root, key, false);
        V retval = null;
        if (result.index == key.length()) {
            retval = result.selfOrParent.value;
        }
        return retval;
    }

    public void remove(String key) {
        var result = search(root, key, false);
        if (result.index == key.length()) {
            if (result.selfOrParent.value != null) {
                --size;
            }
            result.selfOrParent.value = null;
        }
    }

    public boolean contains(String key) {
        var result = search(root, key, false);
        return (
            result.index == key.length() &&
            result.selfOrParent.value != null
        );
    }

    public boolean isEmpty() {
        return this.size == 0;
    }

    public String longestPrefixOf(String s) {
        var result = search(root, s, false);
        return s.substring(0, result.indexOfLongestPrefix + 1);
    }

    private static<V> void enumerate(String prefix, Node<V> root, List<String> keys) {
        if (root != null) {
            if (root.value != null) {
                keys.add(prefix);
            }
            for (var c : root.children.keySet()) {
                enumerate(prefix + c, root.children.get(c), keys);
            }
        }
    }

    public Iterable<String> keysWithPrefix(String s) {
        List<String> retval = new ArrayList<String>();
        var result = search(root, s, false);
        if (result.index == s.length()) {
            enumerate(s, result.selfOrParent, retval);
        }
        return retval;
    }

    private static<V> void searchWithPattern(
        Node<V> root,
        String pattern, // . matches any character
        int start,
        List<String> keys
    ) {
        assert(root != null);
        if (start < pattern.length()) {
            if (pattern.charAt(start) != '.') {
                var child = root.children.get(pattern.charAt(start));
                if (child != null) {
                    searchWithPattern(child, pattern, start + 1, keys);
                }
            } else {
                for (var c : root.children.keySet()) {
                    searchWithPattern(
                        root.children.get(c),
                        pattern.substring(0, start) + c.charValue() + pattern.substring(start + 1),
                        start + 1,
                        keys
                    );
                }
            }
        } else {
            if (root.value != null) {
                keys.add(pattern);
            }
        }
    }

    // all the keys that match s (where . matches any character)
    public Iterable<String> keysThatMatch(String s) {
        List<String> retval = new ArrayList<String>();
        searchWithPattern(root, s, 0, retval);
        return retval;
    }

    public int size() {
        return this.size;
    }

    public Iterable<String> keys() {
        return keysWithPrefix("");
    }

    public static void main(String[] args) {
        Trie<Integer> dictionary = new Trie<Integer>();
        int index = 0;
        dictionary.put("bad", index++);
        assert(dictionary.contains("bad"));
        assert(dictionary.size() == 1);
        dictionary.put("dad", index++);
        assert(dictionary.contains("dad"));
        assert(dictionary.size() == 2);
        dictionary.put("mad", index++);
        assert(dictionary.contains("mad"));
        assert(dictionary.size() == 3);

        dictionary.remove("dad");
        assert(!dictionary.contains("dad"));
        assert(dictionary.size() == 2);

        dictionary.put("pad", index++);
        assert(dictionary.contains("pad"));
        assert(dictionary.size() == 3);

        dictionary.put("pad", index++);
        assert(dictionary.contains("bad"));
        assert(dictionary.size() == 3);

        dictionary.put("1", index++);
        dictionary.put("111", index++);
        dictionary.put("111111", index++);
        dictionary.put("1111111111", index++);
        dictionary.put("111111111111111", index++);
        dictionary.put("111111111111111111111", index++);
        dictionary.put("1111111111111111111111111111", index++);
        dictionary.put("111111111111111111111111111111111111", index++);
        assert(dictionary.size() == 11);
        var iter = dictionary.keysWithPrefix("11").iterator();
        int count = 0;
        while (iter.hasNext()) {
            ++count;
            var next = iter.next();
            assert(next.startsWith("11"));
        }
        assert(count == 7);
        var lp = dictionary.longestPrefixOf("111111111111111111111111111111111111");
        assert(lp.equals("1111111111111111111111111111"));

        count = 0;
        iter = dictionary.keys().iterator();
        while (iter.hasNext()) {
            ++count;
            iter.next();
        }
        assert(count == 11);

        count = 0;
        iter = dictionary.keysThatMatch(".ad").iterator();
        while (iter.hasNext()) {
            ++count;
            var next = iter.next();
            assert(next.substring(1).equals("ad"));
        }
        assert(count == 3);
    }
}
