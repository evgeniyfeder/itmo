package ru.ifmo.rain.feder.student;

import info.kgeorgiy.java.advanced.student.Group;
import info.kgeorgiy.java.advanced.student.Student;

import java.util.*;
import java.util.function.*;
import java.util.stream.Collector;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class StudentDB implements info.kgeorgiy.java.advanced.student.StudentGroupQuery {
    private Function<Student, String> getFullName = s -> s.getFirstName() + " " + s.getLastName();

    private Comparator<Student> normalOrder = Comparator.comparing(Student::getLastName).thenComparing(Student::getFirstName).thenComparing(Student::getId);
    private final String EMPTY_STRING = "";

    private Stream<Map.Entry<String, List<Student>>> getGroupedStream(Collection<Student> collection, Supplier<Map<String, List<Student>>> mapType) {
        return collection.stream()
                .collect(Collectors.groupingBy(Student::getGroup, mapType, Collectors.toList()))
                .entrySet().stream();
    }

    private List<Group> getGroupsBy(Collection<Student> collection, Function<List<Student>, List<Student>> order) {
        return getGroupedStream(collection, TreeMap::new)
                .map(elem -> new Group(elem.getKey(), order.apply(elem.getValue())))
                .collect(Collectors.toList());
    }

    @Override
    public List<Group> getGroupsByName(Collection<Student> collection) {
        return getGroupsBy(collection, this::sortStudentsByName);
    }

    @Override
    public List<Group> getGroupsById(Collection<Student> collection) {
        return getGroupsBy(collection, this::sortStudentsById);
    }


    private String getLargestGroupBy(Collection<Student> collection, Function<List<Student>, Integer> arraySizeGetter) {
        return getGroupedStream(collection, HashMap::new)
                .max(Comparator.comparingInt(
                        (Map.Entry<String, List<Student>> group) -> arraySizeGetter.apply(group.getValue()))
                        .thenComparing(Map.Entry::getKey, Collections.reverseOrder(String::compareTo)))
                .map(Map.Entry::getKey).orElse(EMPTY_STRING);
    }

    @Override
    public String getLargestGroup(Collection<Student> collection) {
        return getLargestGroupBy(collection, List::size);
    }

    @Override
    public String getLargestGroupFirstName(Collection<Student> collection) {
        return getLargestGroupBy(collection, v -> getDistinctFirstNames(v).size());
    }


    ////////////////////////////////////////
    private Stream<String> getMappedStream(List<Student> list, Function<Student, String> func) {
        return list.stream().map(func);
    }

    private List<String> getMappedStudentList(List<Student> list, Function<Student, String> func) {
        return getMappedStream(list, func).collect(Collectors.toList());
    }

    @Override
    public List<String> getFirstNames(List<Student> list) {
        return getMappedStudentList(list, Student::getFirstName);
    }

    @Override
    public List<String> getLastNames(List<Student> list) {
        return getMappedStudentList(list, Student::getLastName);
    }

    @Override
    public List<String> getGroups(List<Student> list) {
        return getMappedStudentList(list, Student::getGroup);
    }

    @Override
    public List<String> getFullNames(List<Student> list) {
        return getMappedStudentList(list, getFullName);
    }

    @Override
    public Set<String> getDistinctFirstNames(List<Student> list) {
        return getMappedStream(list, Student::getFirstName).sorted(String::compareTo).collect(Collectors.toCollection(TreeSet::new));
    }

    @Override
    public String getMinStudentFirstName(List<Student> list) {
        return list.stream().min(Student::compareTo).map(Student::getFirstName).orElse(EMPTY_STRING);
    }

    //////////////////////////////////////////////
    private List<Student> sortStudentsBy(Collection<Student> col, Comparator<Student> comp) {
        return col.stream().sorted(comp).collect(Collectors.toList());
    }

    @Override
    public List<Student> sortStudentsById(Collection<Student> collection) {
        return sortStudentsBy(collection, Student::compareTo);
    }

    @Override
    public List<Student> sortStudentsByName(Collection<Student> collection) {
        return sortStudentsBy(collection, normalOrder);
    }


    //////////////////////////////////////////
    private Stream<Student> getFilteredStream(Collection<Student> collection, Predicate<Student> predicate) {
        return collection.stream().filter(predicate);
    }

    private Stream<Student> getSortedFilteredStream(Collection<Student> collection, Predicate<Student> predicate, Comparator<Student> order) {
        return getFilteredStream(collection, predicate).sorted(order);
    }

    private List<Student> findStudentsBy(Collection<Student> collection, Predicate<Student> predicate) {
        return getSortedFilteredStream(collection, predicate, normalOrder).collect(Collectors.toList());
    }

    @Override
    public List<Student> findStudentsByFirstName(Collection<Student> collection, String s) {
        return findStudentsBy(collection, (Student student) -> student.getFirstName().equals(s));
    }

    @Override
    public List<Student> findStudentsByLastName(Collection<Student> collection, String s) {
        return findStudentsBy(collection, (Student student) -> student.getLastName().equals(s));
    }

    @Override
    public List<Student> findStudentsByGroup(Collection<Student> collection, String s) {
        return findStudentsBy(collection, (Student student) -> s.equals(student.getGroup()));
    }

    @Override
    public Map<String, String> findStudentNamesByGroup(Collection<Student> collection, String s) {
        return getFilteredStream(collection, (Student student) -> s.equals(student.getGroup()))
                .collect(Collectors.toMap(Student::getLastName, Student::getFirstName, BinaryOperator.minBy(String::compareTo)));
    }
}
