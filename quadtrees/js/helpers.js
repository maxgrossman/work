function _remove_from_list(list, index) {
    if (list.length - 1 === index)
        list.pop()
    else
        list[index] = list.pop();
}

function query_contains_point(bounds, point) {
    if (bounds[0] > point[0]) {
        return false;
    }

    if (bounds[1] > point[1]) {
        return false;
    }

    if (point[0] > bounds[2]) {
        return false;
    }

    if (point[1] > bounds[3]) {
        return false;
    }

    return true;
}

module.exports = {
    _remove_from_list: _remove_from_list,
    query_contains_point: query_contains_point
}
