package ru.ifmo.rain.feder.arrayset;

import java.util.AbstractList;
import java.util.List;

class ReversedList<T> extends AbstractList<T> {
    private List<T> elements;
    private boolean isReversed;

    ReversedList(List<T> list) {
        elements = list;
    }

    @Override
    public T get(int index) {
        return !isReversed ? elements.get(index) : elements.get(elements.size() - 1 - index);
    }

    @Override
    public int size() {
        return elements.size();
    }

    public void reverse() {
        isReversed = !isReversed;
    }

    boolean getReverseFlag() {
        return isReversed;
    }

    List<T> getElements() {
        return elements;
    }
}
