<?php
/**
 * @file
 * sortable_list.theme.inc
 */

/**
 * @param $variables
 */
function theme_sortable_list($variables) {
  $elements = $variables['elements'];
  $table_element = array();
  foreach (array('header', 'attributes') as $key) {
    if (isset($elements['#' . $key])) {
      $table_element[$key] = $elements['#' . $key];
      unset($elements['#' . $key]);
    }
  }

  foreach (element_children($elements) as $item_index) {
    $row = array('data' => array());
    if (isset($elements[$item_index]['#attributes'])) {
      $row += $elements[$item_index]['#attributes'];
    }

    foreach (element_children($elements[$item_index]) as $cell_key) {
      $child = $elements[$item_index][$cell_key];
      $cell = array('data' => drupal_render($child));
      if (isset($child['#cell_attributes'])) {
        $cell += $child['#cell_attributes'];
      }
      $row['data'][] = $cell;
    }
    $table_element['rows'][] = $row;
    unset($elements[$item_index]);
  }

  $elements['#children'] = theme('table', $table_element);
  return theme('form_element', $elements);
}
