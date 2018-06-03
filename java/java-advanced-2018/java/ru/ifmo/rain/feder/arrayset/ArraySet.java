package ru.ifmo.rain.feder.arrayset;

import java.util.*;

public class ArraySet<T> extends AbstractSet<T> implements NavigableSet<T> {
    private List<T> elements;
    private Comparator<? super T> comparator;

    public ArraySet() {
        elements = Collections.emptyList();
    }

    public ArraySet(Collection<? extends T> collection) {
        elements = new ArrayList<>(new TreeSet<>(collection));
    }

    private ArraySet(Comparator<? super T> newComparator) {
        elements = Collections.emptyList();
        comparator = newComparator;
    }

    public ArraySet(Collection<? extends T> collection, Comparator<? super T> newComparator) {
        NavigableSet<T> set = new TreeSet<>(newComparator);
        comparator = newComparator;

        set.addAll(collection);
        elements = new ArrayList<>(set);
    }

    private ArraySet(List<T> collection, Comparator<? super T> newComparator) {
        elements = collection;
        comparator = newComparator;
    }

    private boolean checkSize(int ind) {
        return ind >= 0 && ind < elements.size();
    }

    private int findInd(T t, int found, int notFound) {
        int ind = Collections.binarySearch(elements, Objects.requireNonNull(t), comparator);
        if (ind < 0) {
            ind = -ind - 1;
            return checkSize(ind + notFound) ? ind + notFound : -1;
        }
        return checkSize(ind + found) ? ind + found : -1;
    }

    private T findElem(T t, int found, int notFound) {
        int ind = findInd(t, found, notFound);
        return checkSize(ind) ? elements.get(ind) : null;
    }

    @Override
    public T lower(T t) {
        return findElem(t, -1, -1);
    }

    @Override
    public T floor(T t) {
        return findElem(t, 0, -1);
    }

    @Override
    public T ceiling(T t) {
        return findElem(t, 0, 0);
    }

    @Override
    public T higher(T t) {
        return findElem(t, 1, 0);
    }

    @Override
    public T pollFirst() {
        throw new UnsupportedOperationException();
    }

    @Override
    public T pollLast() {
        throw new UnsupportedOperationException();
    }

    @Override
    public Iterator<T> iterator() {
        return Collections.unmodifiableList(elements).iterator();
    }

    @Override
    public NavigableSet<T> descendingSet() {
        ReversedList<T> revElement = null;

        if (elements instanceof ReversedList) {
            revElement = new ReversedList<>(((ReversedList<T>) elements).getElements());

            if (!((ReversedList) elements).getReverseFlag())
                revElement.reverse();
        } else {
            revElement = new ReversedList<>(elements);
            revElement.reverse();
        }
        return new ArraySet<T>(revElement, Collections.reverseOrder(comparator));
    }

    @Override
    public Iterator<T> descendingIterator() {
        return descendingSet().iterator();
    }


    @Override
    public NavigableSet<T> subSet(T fromElement, boolean fromInclusive, T toElement, boolean toInclusive) {
        int
                fromInd = fromInclusive ? findInd(fromElement, 0, 0) : findInd(fromElement, 1, 0),
                endInd = toInclusive ? findInd(toElement, 0, -1) : findInd(toElement, -1, -1);
        if (fromInd > endInd || fromInd == -1 || endInd == -1) {
            return new ArraySet<>(comparator);
        }
        return new ArraySet<>(elements.subList(fromInd, endInd + 1), comparator);
    }

    @Override
    public NavigableSet<T> headSet(T toElement, boolean inclusive) {
        if (elements.size() == 0)
            return new ArraySet<>(comparator);
        return subSet(first(), true, toElement, inclusive);
    }

    @Override
    public NavigableSet<T> tailSet(T fromElement, boolean inclusive) {
        if (elements.size() == 0)
            return new ArraySet<>(comparator);
        return subSet(fromElement, inclusive, last(), true);
    }

    @Override
    public Comparator<? super T> comparator() {
        return comparator;
    }

    @Override
    public SortedSet<T> subSet(T fromElement, T toElement) {
        return subSet(fromElement, true, toElement, false);
    }

    @Override
    public SortedSet<T> headSet(T toElement) {
        return headSet(toElement, false);
    }

    @Override
    public SortedSet<T> tailSet(T fromElement) {
        return tailSet(fromElement, true);
    }

    @Override
    public T first() {
        if (elements.isEmpty())
            throw new NoSuchElementException();
        return elements.get(0);
    }

    @Override
    public T last() {
        if (elements.isEmpty())
            throw new NoSuchElementException();
        return elements.get(elements.size() - 1);
    }

    @Override
    public int size() {
        return elements.size();
    }

    @Override
    public boolean contains(Object o) {
        return Collections.binarySearch(elements, (T) Objects.requireNonNull(o), comparator) >= 0;
    }
}
