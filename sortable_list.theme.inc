<?php
/**
 * @file
 * sortable_list.theme.inc
 */

/**
 * @param $variables
 */
function theme_sortable_list_field_data_items_ui($variables) {
  $elements = $variables['elements'];
  $table = array();

  foreach (array('header', 'attributes') as $key) {
    if (isset($elements['#' . $key])) {
      $table[$key] = $elements['#' . $key];
    }
  }

  foreach (element_children($elements) as $row_key) {
    $row = array('data' => array());
    if (isset($elements[$row_key]['#attributes'])) {
      $row += $elements[$row_key]['#attributes'];
    }

    foreach (element_children($elements[$row_key]) as $cell_key) {
      $child = $elements[$row_key][$cell_key];
      $cell = array('data' => drupal_render($child));
      if (isset($child['#cell_attributes'])) {
        $cell += $child['#cell_attributes'];
      }
      $row['data'][] = $cell;
    }

    $table['rows'][] = $row;
  }

  $output = array(
    '#type' => 'container',
    'data_table' => array(
      '#type' => 'markup',
      '#markup' => theme('table', $table),
    ),
  );
  if (isset($elements['actions'])) {
    $output['actions'] = $elements['actions'];
  }

  return drupal_render($output);
}
